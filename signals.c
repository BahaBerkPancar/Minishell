/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpancar <bpancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:37:25 by skalkan           #+#    #+#             */
/*   Updated: 2025/08/24 00:43:09 by bpancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		g_signal_exit = 0;

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
		exit(0);
	g_signal_exit = 130;
}
