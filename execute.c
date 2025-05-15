#include <minishell.h>

void	execute(char *path, char **flags, t_vault *vault)
{
	if(execve(path, flags, vault->envp) == -1)
	{
		perror("execve");
		exit(1);
	}
}

char	**get_flags(t_input **input, char *command)
{
	char **flags;
	char *tmp1;
	t_input *tmp;

	tmp = *input;
	while(tmp->value != command)
		tmp = tmp->next;
	tmp1 = ft_strjoin(tmp->value, " ");
	while(tmp->next && (tmp->next->type != PIPE && tmp->next->type != TOKEN))
	{
		tmp1 = ft_strjoin(tmp1, " ");
		tmp1 = ft_strjoin(tmp1, tmp->next->value);
		tmp = tmp->next;
	}
	flags = ft_split(tmp1, ' ');
	return (flags);
}

void	tmp_execute(t_input **input, t_vault *vault)
{
	t_input	*tmp;
	int		fd[2];
	int		flag;
	char	**flags;
	int		heredoc_fd;

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
			{
				printf("minishell: %s: No such file or directory\n", tmp->value);
				exit(1);
			}
			dup2(fd[0], 0);
			close(fd[0]);
		}
		else if(tmp->type == REDIRECT_OUTPUT)
		{
			fd[1] = open(tmp->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if(fd[1] == -1)
			{
				printf("minishell: %s: Permission denied\n", tmp->value);
				exit_ms(vault, 1);
			}
			dup2(fd[1], 1);
			close(fd[1]);
		}
		else if(tmp->type == APPEND_OUTPUT)
		{
			fd[1] = open(tmp->value, O_WRONLY | O_CREAT | O_APPEND, 0777);
			if(fd[1] == -1)
			{
				printf("minishell: %s: Permission denied\n", tmp->value);
				exit_ms(vault, 1);
			}
			dup2(fd[1], 1);
			close(fd[1]);
		}
		else if(tmp->type == HEREDOC)
		{
			heredoc_fd = heredoc(tmp->value);
			dup2(heredoc_fd, STDIN_FILENO);
			close(heredoc_fd);
		}
		else if(tmp->type == COMMAND && flag == 1)
		{
			flags = get_flags(input, tmp->value);
			flag = 0;
		}
		tmp = tmp->next;
	}
	if(is_executable(flags[0]))
		execute(set_path(flags[0]), flags, vault);
	else
		printf("command not found\n");
	exit_ms(vault, 1);
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
	return (1);
}
