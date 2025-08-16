#include "../include/minishell.h"

int		g_signal_exit = 0;

int	*get_exit_status_code(void)
{
	static int	exit_status_code = 0;
	
	return (&exit_status_code);
}
void	handle_sigint(int sig)
{
	(void)sig;
	if (g_signal_exit == 0 || g_signal_exit == 130)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (g_signal_exit == 2)
	{
		write(1, "\n", 1);
		rl_on_new_line();
	}
	else if (g_signal_exit == 1)
	{
		
		exit(0);
	}
	// set_exit_status_code(130);
	g_signal_exit = 130;
}
