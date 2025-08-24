/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpancar <bpancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:48:04 by skalkan           #+#    #+#             */
/*   Updated: 2025/08/24 03:47:18 by bpancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}

void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	free(arr);
}

char	*remove_slash(const char *path)
{
	int		len;
	char	*copy;

	if (!path || !*path)
		return (NULL);
	copy = ft_strdup(path);
	if (!copy)
		return (NULL);
	len = ft_strlen(copy);
	if (len > 1 && copy[len - 1] == '/')
		copy[len - 1] = '\0';
	return (copy);
}

bool	is_executable(t_vault *vault, char *string, char *full_path, int i)
{
	char		**paths;
	char		*tmp;
	struct stat	st;

	tmp = remove_slash(string);
	if (!tmp)
		return (false);
	if (ft_strchr(tmp, '/') && stat(tmp, &st) == 0
		&& S_ISREG(st.st_mode) && access(tmp, X_OK) == 0)
		return (free(tmp), true);
	paths = get_path(vault);
	if (!paths)
		return (free(tmp), false);
	while (paths[++i])
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin_free(full_path, tmp);
		if (!full_path)
			return (free_split(paths), free(tmp), false);
		if (stat(full_path, &st) == 0 && S_ISREG(st.st_mode)
			&& access(full_path, X_OK) == 0)
			return (free(tmp), free_split(paths), free(full_path), true);
		free(full_path);
	}
	return (free_split(paths), free(tmp), false);
}

bool	is_main_builtin(const char *cmd)
{
	return (ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}
