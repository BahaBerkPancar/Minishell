/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpancar <bpancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:51:29 by skalkan           #+#    #+#             */
/*   Updated: 2025/08/24 00:37:27 by bpancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	*get_exit_status_code(void)
{
	static int	exit_status_code = 0;

	return (&exit_status_code);
}

void	set_exit_status_code(int exit_code)
{
	int	*static_exit_code;

	static_exit_code = get_exit_status_code();
	*static_exit_code = exit_code;
}

void	closed(int fd, int fd1)
{
	if (fd != -1 && fd1 != -1)
		dup2(fd, fd1);
	if (fd != -1 && fd1 == -1)
		close(fd);
}
