#include <minishell.h>

int tmp_builtin(char *input, t_vault *vault)
{
	if(ft_strcmp(input, "pwd") == 0)
		pwd();
	else if(ft_strcmp(input, "clear") == 0)
		clear();
	else if(ft_strncmp(input, "cd", 2) == 0)
		cd(input + 2, vault);
	else if(ft_strcmp(input, "exit") == 0)
		exit(0);
	else if(ft_strcmp(input, "env") == 0)
	{
		for(int i = 0; vault->envp[i]; i++)
			printf("%s\n", vault->envp[i]);
	}
	else
		return (1);
	return (0);
}