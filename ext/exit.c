/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skalkan <skalkan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:51:29 by skalkan           #+#    #+#             */
/*   Updated: 2025/08/23 23:51:41 by skalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	cleanup_and_exit(t_input **input, char **flags, t_vault *vault)
{
	free_pointer(flags);
	free_input_list(input);
	free_vault(vault);
	exit(0);
}
