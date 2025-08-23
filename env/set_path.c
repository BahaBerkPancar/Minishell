/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skalkan <skalkan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:46:35 by skalkan           #+#    #+#             */
/*   Updated: 2025/08/23 23:46:36 by skalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*set_path(t_vault *vault, char *input)
{
	char	*path;
	char	*tmp;
	char	**paths;
	int		i;

	if (ft_strchr(input, '/'))
		return (input);
	path = vault_getenv(vault, "PATH");
	paths = ft_split(path, ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		tmp = ft_strjoin(tmp, input);
		if (access(tmp, F_OK) == 0)
		{
			free(paths[i]);
			return (tmp);
		}
		free(tmp);
		i++;
	}
	return (NULL);
}
