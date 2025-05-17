#include <minishell.h>

void	execute(char *path, char **flags, t_vault *vault)
{
	if(execve(path, flags, vault->envp) == -1)
	{
		perror("execve");
		exit_ms(vault, 127);
	}
}

static int	count_args(t_input *input)
{
	int count;
	t_input *tmp;

	count = 0;
	tmp = input->next;
	while (tmp && tmp->type != PIPE && tmp->type != TOKEN)
	{
		count++;
		tmp = tmp->next;
	}
	return count;
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

void	tmp_execute(t_input **input, t_vault *vault)
{
	t_input	*tmp;
	int		fd[2];
	int		flag;
	char	**flags;

	tmp = *input;
	flag = 1;
	while(tmp)
	{
		if(tmp->type == TOKEN)
			;
		else if(tmp->type == REDIRECT_INPUT)
		{
			fd[0] = open(tmp->value, O_RDONLY);
			if(fd[0] == -1)
				return((void)printf("minishell: %s: No such file or directory\n", tmp->value),
					closed(fd[0], -1), exit_ms(vault, 1));
			closed(fd[0], STDIN_FILENO);
		}
		else if(tmp->type == REDIRECT_OUTPUT || tmp->type == APPEND_OUTPUT)
		{
			if(tmp->type == REDIRECT_OUTPUT)
				fd[1] = open(tmp->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else
				fd[1] = open(tmp->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if(fd[1] == -1)
				return((void)printf("minishell: %s: Permission denied\n", tmp->value),
					closed(fd[1], -1), exit_ms(vault, 1));
			closed(fd[1], STDOUT_FILENO);
		}
		else if(tmp->type == HEREDOC)
			closed(heredoc(tmp->value), STDIN_FILENO);
		else if(tmp->type == COMMAND && flag--)
			flags = get_flags(input, tmp->value);
		tmp = tmp->next;
	}
	if(is_executable(flags[0]))
		execute(set_path(flags[0]), flags, vault);
	else
		return((void)printf("command not found\n"), exit_ms(vault, 127));
}

int	real_execute(t_input **input, t_vault *vault)
{
	pid_t	pid;
	pid_t	pid1;
	int		fd[2];
	// t_input *tmp;

	pid = fork();
	if(pipe_count(input) && pid == 0)
	{
		pipe(fd);
		pid1 = fork();
		if(pid1 == 0)
		{
			close(fd[1]);
			dup2(fd[0], 0);
			close(fd[0]);
			while((*input)->type != PIPE)
				delete_node(input, *input);
			delete_node(input, *input);
			tmp_execute(input, vault);
		}
		else
		{
			close(fd[0]);
			dup2(fd[1], 1);
			close(fd[1]);
			tmp_execute(input, vault);
		}
	}
	else
	{
		if(pid == 0)
			tmp_execute(input, vault);
		else
		{
			waitpid(pid, NULL, 0);
			// ft_lstprint(*input);
		}
	}
	return (free_input(*input), 1);
}
