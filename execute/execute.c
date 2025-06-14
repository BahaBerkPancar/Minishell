#include <minishell.h>

void	execute(char *path, char **flags, t_vault *vault)
{			//bin/ls ls  la infile
	if(execve(path, flags, vault->envp) == -1)
	{
		perror("execve");
		exit_ms(vault, 127);
	}
	exit(1);
}

void	open_pipe(int **fd, int j)
{
	int i;

	i = 0;
	while(i < j)
	{
		fd[i] = (int *)malloc(sizeof(int) * 2);
		pipe(fd[i]);
		i++;
	}
}

bool has_next_pipe(t_input *node)
{
	while (node)
	{
		if (node->type == PIPE)
			return (true);
		node = node->next;
	}
	return (false);
}


char **build_argv_until_pipe(t_input **node)
{
	t_input *tmp;
	int count = 0;
	t_input *tmp1;
	char **argv;
	int i;

	i = 0;
	tmp = *node;
	tmp1 = tmp;
	while (tmp1 && tmp1->type != PIPE)
	{
		if (tmp1->type == COMMAND || tmp1->type == ARGUMANT ||
			tmp1->type == FLAG || tmp1->type == VARIABLE || tmp1->type == BUILTIN)
			count++;
		tmp1 = tmp1->next;
	}
	argv = malloc(sizeof(char *) * (count + 1));
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == COMMAND || tmp->type == ARGUMANT ||
			tmp->type == FLAG || tmp->type == VARIABLE || tmp->type == BUILTIN)
			argv[i++] = ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	argv[i] = NULL;
	if (tmp && tmp->type == PIPE)
		tmp = tmp->next;
	*node = tmp;
	return (argv);
}


int execute_pipe(t_input **input, t_vault *vault)
{
	t_input *tmp = *input;
	pid_t	pid;
	int		pipe_fds[2];
	int		prev_read_end = -1;
	int		status;

	while (tmp)
	{
		pipe(pipe_fds);
		pid = fork();
		if (pid == 0)
		{
			closed(prev_read_end, 0);
			if (has_next_pipe(tmp))
				dup2(pipe_fds[1], 1);
			close(pipe_fds[0]);
			close(pipe_fds[1]);
			tmp_execute(input, vault, 0);
			execute_command(input, build_argv_until_pipe(&tmp), vault);
		}
		else if (pid > 0)
		{
			close(pipe_fds[1]);
			closed(prev_read_end, -1);
			prev_read_end = pipe_fds[0];
			while (tmp && tmp->type != PIPE)
				tmp = tmp->next;
			if (tmp)
				tmp = tmp->next; 
		}
	}
	while (wait(&status) > 0);
	return (0);
}

int	real_execute(t_input **input, t_vault *vault)
{
	pid_t	pid;

	if (pipe_count(input))
	{
		pid = fork();
		if(pid == 0)
			execute_pipe(input, vault);
		else
			waitpid(pid, NULL, 0);
	}
	else if (pipe_count(input) == 0)
	{
		pid = fork();
		if (pid == 0)
			tmp_execute(input, vault, 1);
		else
			waitpid(pid, NULL, 0);
	}
	return (1);
}

