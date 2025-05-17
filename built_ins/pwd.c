#include <minishell.h>

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

int	cd(char *path, t_vault *vault)
{
	path = ft_strtrim(path, " ");
	if (path == NULL || ft_strcmp(path, "~") == 0)
		path = vault->home;
	if (ft_strcmp(path, "-") == 0)
	{
		printf("%s\n", vault->oldpwd);
		path = vault->oldpwd;
	}
	if (chdir(path) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", path);
		return (1);
	}
	vault->oldpwd = vault->pwd;
	vault->pwd = getcwd(NULL, 0);
	update_or_add_var(ft_strjoin("OLDPWD=", vault->oldpwd), vault);
	update_or_add_var(ft_strjoin("PWD=", vault->pwd), vault);
	return (0);
}
