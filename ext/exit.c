#include <minishell.h>

void	exit_code(t_vault *vault, int exit_status)
{
	vault->exit_status = exit_status;
}

void	exit_ms(t_vault *vault, int exit_status)
{
	if (exit_status == 0)
		exit(vault->exit_status);
	else
		exit(exit_status);
}

void	closed(int fd, int fd1)
{
	if (fd != -1)
		dup2(fd, fd1);
	if (fd != -1)
		close(fd);
}
