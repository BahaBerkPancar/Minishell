#include "../include/minishell.h"

void	execute_command(t_input **input, char **flags, t_vault *vault)
{
	if (flags && is_builtin(flags[0]))
		builtin(input, flags, vault, 1);
	else if (flags && is_executable(vault, flags[0]) && !is_builtin(flags[0]))
		execute(set_path(vault, flags[0]), flags, vault);
	else
	{
		free_pointer(flags);
		free_input_list(input);
		free_vault(vault);
		printf("Command not found\n");
		exit(127);
	}
}

static char	**get_flags(t_input **input, char *cmd)
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

bool is_main_builtin(const char *cmd)
{
	return (ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}

bool execute_builtin_in_main(t_input **input, t_vault *vault)
{
	t_input	*tmp;
	char	**flags;
	int		stdin_copy;
	int		stdout_copy;

	if (!input || !*input)
		return (false);
	tmp = *input;
	while (tmp && tmp->type != COMMAND && tmp->type != BUILTIN)
		tmp = tmp->next;
	if (!tmp || !is_main_builtin(tmp->value))
		return (false);
	flags = get_flags(input, tmp->value);
	if (!flags)
		return (false);
	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	tmp_execute(input, vault, 0);
	builtin(input, flags, vault, 0);
	dup2(stdin_copy, STDIN_FILENO);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdin_copy);
	close(stdout_copy);
	free_pointer(flags);
	return (true);
}

void	tmp_execute(t_input **input, t_vault *vault, int x)
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
