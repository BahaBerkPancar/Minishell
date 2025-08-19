#include "../include/minishell.h"

int	heredoc_read_write(int *fd, char *delimiter, int heredoc_status)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (!input)
		{
			heredoc_status = -1;
			break ;
		}
		if (ft_strcmp(input, delimiter) == 0)
		{
			free(input);
			break ;
		}
		write(*fd, input, ft_strlen(input));
		write(*fd, "\n", 1);
		free(input);
	}
	return (heredoc_status);
}
static char	*cpy_heredock(char *str,  t_input **final, t_vault *vault)
{
	static char	delimiter[10000];
	int			i;

	i = -1;
	while (str[++i])
		delimiter[i] = str[i];
	delimiter[i] = '\0';
	free_vault(vault);
	free_input_list(final);
	return (delimiter);
}

int	wait_child(pid_t pid, t_vault *vault)
{
	int		status;
	pid_t	ended_pid;

	set_exit_status(vault, 0);
	ended_pid = wait(&status);
	while (ended_pid > 0)
	{
		if (ended_pid == pid && WIFEXITED(status))
			set_exit_status(vault, WEXITSTATUS(status));
		ended_pid = wait(&status);
	}
	return (0);
}

void	heredoc(char *delimiter, int built_in, t_input **final, t_vault *vault)
{
	int		fd[2];
	pid_t	pid;
	char	*str;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		str = cpy_heredock(delimiter, final, vault);
		g_signal_exit = 1;
		close(fd[0]);
		if(heredoc_read_write(&fd[1], str, 0) == -1)
			exit(0);
		close(fd[1]);
		exit(0);
	}
	else
	{
		close(fd[1]);
		if (wait_child(pid, vault) == 130)
			return ;
		if (built_in == 0)
			dup2(fd[0], 0);
	}
}
