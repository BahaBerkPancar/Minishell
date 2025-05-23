#include <minishell.h>

void	execute(char *path, char **flags, t_vault *vault)
{
	// int		prev_fd;

	// prev_fd = open("a", O_WRONLY | O_CREAT | O_APPEND, 0644);
	// write(prev_fd, "execute\n", 8);
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

static void	execute_command(t_input **input, char **flags, t_vault *vault)
{
	if (flags && is_builtin(flags[0]))
		builtin(input, flags, vault);
	else if (flags && is_executable(flags[0]) && !is_builtin(flags[0]))
		execute(set_path(flags[0]), flags, vault);
	else
	{
		printf("Command not found\n");
		exit_ms(vault, 127);
	}
}

void	tmp_execute(t_input **input, t_vault *vault)
{
	t_input	*tmp;
	int		flag;
	char	**flags;

	tmp = *input;
	flag = 1;
	while (tmp)
	{
		if (tmp->type == TOKEN)
			;
		else if (tmp->type == REDIRECT_INPUT && !handle_input_redirect(tmp, vault))
			return ;
		else if ((tmp->type == REDIRECT_OUTPUT || tmp->type == APPEND_OUTPUT)
			&& !handle_output_redirect(tmp, vault))
			return ;
		else if (tmp->type == HEREDOC)
			closed(heredoc(tmp->value), STDIN_FILENO);
		else if (tmp->type == COMMAND && flag--)
			flags = get_flags(input, tmp->value);
		else if (tmp->type == BUILTIN && flag--)
			flags = get_flags(input, tmp->value);
		tmp = tmp->next;
	}
	execute_command(input, flags, vault);
}

int	execute_pipe(t_input **input, t_vault *vault)
{
	t_input	*tmp;
	pid_t	pid;
	int		pr_fd[2];
	int		cr_fd[2];
	int		flag;

	tmp = *input;
	flag = 0;
	pipe(pr_fd);
	while(tmp && pipe_count(&tmp) > 0)
	{
		pipe(cr_fd);
		pid = fork();
		if(pid == 0)
		{
			dup2(cr_fd[1], 1);
			close(cr_fd[1]);
			if(flag != 0)
				dup2(pr_fd[0], 0);
			close(pr_fd[0]);
			flag++;
			tmp_execute(&tmp, vault);
			exit(0);
		}
		else
		{
			waitpid(pid, NULL, 0);
			while(tmp && tmp->type != PIPE)
				tmp = tmp->next;
			if(tmp->next)
				tmp = tmp->next;
			pr_fd[0] = cr_fd[0];
			pr_fd[1] = cr_fd[1];
		}
		// printf("asd1\n");
	}
	close(cr_fd[1]);
	dup2(pr_fd[0], 0);
	close(pr_fd[0]);
	close(cr_fd[0]);
	close(pr_fd[1]);
	printf("");
	tmp_execute(&tmp, vault);
	return (0);
}


int	real_execute(t_input **input, t_vault *vault)
{
	pid_t	pid;

	if (pipe_count(input))
	{
		// printf("pipe\n");
		pid = fork();
		if(pid == 0)
			execute_pipe(input, vault);
		else
			waitpid(pid, NULL, 0);
		// ft_lstprint(*input);
	}
	else if (pipe_count(input) == 0)
	{
		pid = fork();
		if (pid == 0)
			tmp_execute(input, vault);
		else
		{
			waitpid(pid, NULL, 0);
			// ft_lstprint(*input);
		}
	}
	return (free_input(*input), 1);
}

