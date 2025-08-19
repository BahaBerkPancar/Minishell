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

int cd(char *path, t_vault *vault)
{
    char *tmp;
    bool owns_path = false;      

    // printf("Changing directory to: %s\n", path);
    tmp = ft_strdup(path);               
    path = ft_strtrim(tmp, " /");
    free(tmp);
    owns_path = true;
    if (path == NULL || ft_strcmp(path, "~") == 0)
    {
        free(path);
        path = vault->home;              
        owns_path = false;
    }
    if (ft_strcmp(path, "-") == 0)
    {
        printf("%s\n", vault->oldpwd);
        if (owns_path)
            free(path);
        path = ft_strdup(vault->oldpwd); 
        owns_path = true;
    }
    if (chdir(path) == -1)
    {
        printf("minishell: cd: %s: No such file or directory\n", path);
        if (owns_path)
            free(path);
        return 1;
    }
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
    if (owns_path)
        free(path);
    return 0;
}
