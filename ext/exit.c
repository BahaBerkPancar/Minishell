#include "../include/minishell.h"

void	set_exit_status(t_vault *vault, int exit_status)
{
	vault->exit_status = exit_status;
}

void	exit_ms(t_vault *vault, int exit_status)
{
	set_exit_status(vault, exit_status);
	exit(exit_status);
}

void	closed(int fd, int fd1)
{
	if (fd != -1 && fd1 != -1)
		dup2(fd, fd1);
	if (fd != -1 && fd1 == -1)
		close(fd);
}
