#include "../include/minishell.h"

char	**get_flags(t_input **input, char *cmd)
{
	t_input	*tmp;
	int		i;
	int		argc;
	char	**flags;

	i = 0;
	tmp = *input;
	while (tmp && ft_strcmp(tmp->value, cmd) != 0)
		tmp = tmp->next;
	if (!tmp)
		return (NULL);
	argc = count_args(tmp);
	flags = malloc((argc + 2) * sizeof(char *));
	if (!flags)
		return (NULL);
	flags[i++] = ft_strdup(cmd);
	tmp = tmp->next;
	while (tmp && tmp->type != PIPE && tmp->type != TOKEN)
	{
		flags[i++] = ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	flags[i] = NULL;
	return (flags);
}

static int	handle_input_redirect(t_input *tmp, t_vault *vault)
{
	int	fd;

	fd = open(tmp->value, O_RDONLY);
	if (fd == -1)
	{
		printf("minishell: %s: No such file or directory\n", tmp->value);
		closed(fd, -1);
		exit_ms(vault, 1);
		return (0);
	}
	closed(fd, STDIN_FILENO);
	return (1);
}

static int	handle_output_redirect(t_input *tmp, t_vault *vault)
{
	int	fd;

	fd = 0;
	if (tmp->type == REDIRECT_OUTPUT)
		fd = open(tmp->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (tmp->type == APPEND_OUTPUT)
		fd = open(tmp->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		printf("minishell: %s: Permission denied\n", tmp->value);
		closed(fd, -1);
		exit_ms(vault, 1);
		return (0);
	}
	closed(fd, STDOUT_FILENO);
	return (1);
}

void	redir_execute(t_input **input, t_vault *vault, int x)
{
	t_input	*tmp;
	int		flag;
	char	**flags;

	tmp = *input;
	flag = 1;
	flags = NULL;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == REDIRECT_INPUT && !handle_input_redirect(tmp, vault))
			return ;
		else if ((tmp->type == REDIRECT_OUTPUT || tmp->type == APPEND_OUTPUT)
			&& !handle_output_redirect(tmp, vault))
			return ;
		else if (tmp->type == TOKEN && ft_strcmp(tmp->value, "<<") == 0)
		{
			heredoc(tmp->next->value, input, vault, flags);
			tmp = tmp->next;
		}
		else if ((tmp->type == COMMAND || tmp->type == BUILTIN) && flag-- && x)
			flags = get_flags(input, tmp->value);
		tmp = tmp->next;
	}
	if (x)
		execute_command(input, flags, vault);
}
