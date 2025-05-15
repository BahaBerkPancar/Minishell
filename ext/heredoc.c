#include <minishell.h>

int	heredoc(char *str)
{
	int		fd[2];
	pid_t	pid;
	char	*line;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		while (1)
		{
			line = readline("> ");
			if (!line || ft_strcmp(line, str) == 0)
				break;
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
			free(line);
		}
		free(line);
		close(fd[1]);
		exit(0);
	}
	close(fd[1]);
	waitpid(pid, NULL, 0);
	return (fd[0]);
}
