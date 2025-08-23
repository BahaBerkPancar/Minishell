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
static char	*cpy_heredock(char *str)
{
	char	*delimiter;

	delimiter = ft_strdup(str);
	if (!delimiter)
		return (NULL);
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

void	heredoc(char *delimiter, t_input **final, t_vault *vault, char **flags)
{
	int		fd[2];
	pid_t	pid;
	char	*str;

	pipe(fd);
	pid = fork();
	(void)final;
	if (pid == 0)
	{
		str = cpy_heredock(delimiter);
		g_signal_exit = 1;
		close(fd[0]);
		if(heredoc_read_write(&fd[1], str, 0) == -1)
		{
			free(str);
			free_pointer(flags);
			free_vault(vault);
			// free_input_list(final);
			exit(0);
		}
		free_vault(vault);
		free(str);
		close(fd[1]);
		free_pointer(flags);
		// free_input_list(final);
		exit(0);
	}
	else
	{
		close(fd[1]);
		if (wait_child(pid, vault) == 130)
			return (free_pointer(flags));
		dup2(fd[0], STDIN_FILENO);
	}
}
