/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skalkan <skalkan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:43:39 by skalkan           #+#    #+#             */
/*   Updated: 2025/08/23 23:43:41 by skalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
		return (1);
	printf("%s\n", path);
	free(path);
	return (0);
}
