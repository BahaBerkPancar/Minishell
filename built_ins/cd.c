/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skalkan <skalkan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:42:30 by skalkan           #+#    #+#             */
/*   Updated: 2025/08/23 23:42:32 by skalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*handle_home(char *path, t_vault *vault, int *owns_path)
{
	if (path == NULL || ft_strcmp(path, "~") == 0)
	{
		free(path);
		*owns_path = 0;
		return (vault->home);
	}
	return (path);
}

static char	*handle_oldpwd(char *path, t_vault *vault, int *owns_path)
{
	if (ft_strcmp(path, "-") == 0)
	{
		printf("%s\n", vault->oldpwd);
		if (*owns_path)
			free(path);
		*owns_path = 1;
		return (ft_strdup(vault->oldpwd));
	}
	return (path);
}

static int	change_directory(char *path, int owns_path)
{
	if (chdir(path) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", path);
		if (owns_path)
			free(path);
		return (1);
	}
	return (0);
}

static void	update_pwd_vars(t_vault *vault)
{
	char	*tmp;

	free(vault->oldpwd);
	vault->oldpwd = ft_strdup(vault->pwd);
	free(vault->pwd);
	vault->pwd = getcwd(NULL, 0);
	tmp = ft_strjoin("OLDPWD=", vault->oldpwd);
	update_or_add_var(tmp, vault);
	free(tmp);
	tmp = ft_strjoin("PWD=", vault->pwd);
	update_or_add_var(tmp, vault);
	free(tmp);
}

int	cd(char *path, t_vault *vault)
{
	char	*tmp;
	int		owns_path;

	owns_path = 0;
	tmp = ft_strdup(path);
	path = ft_strdup(tmp);
	free(tmp);
	owns_path = 1;
	path = handle_home(path, vault, &owns_path);
	path = handle_oldpwd(path, vault, &owns_path);
	if (change_directory(path, owns_path))
		return (1);
	update_pwd_vars(vault);
	if (owns_path)
		free(path);
	return (0);
}
