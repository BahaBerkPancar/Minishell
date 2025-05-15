#include <minishell.h>

void	exit_ms(t_vault *vault, int exit_status)
{
	if (exit_status == 0)
		exit(vault->exit_status);
	else
		exit(exit_status);
}
