#include "../include/minishell.h"

void	builtin(t_input **input, char **flags, t_vault *vault, int x)
{
	int		i;

	i = 0;
	if(ft_strcmp(flags[0], "echo") == 0 && ft_strlen(flags[0]) == 4)
		echo(flags);
	else if(ft_strcmp(flags[0], "cd") == 0 && ft_strlen(flags[0]) == 2)
	{
		// printf("Executing cd with flags: %s\n", flags[1]);
		if (flags[1] && !flags[2])
			cd(flags[1], vault);
		else if(!flags[1])
			cd("", vault);
		else
			printf("minishell: cd: too many arguments\n");
	}
	else if(ft_strcmp(flags[0], "pwd") == 0 && ft_strlen(flags[0]) == 3)//////////////////////////
	{
		if(!flags[1])
			pwd();
		else
			printf("minishell: pwd: too many arguments\n");
	}
	else if(ft_strcmp(flags[0], "export") == 0 && ft_strlen(flags[0]) == 6)
		export(input, vault);
	else if(ft_strcmp(flags[0], "unset") == 0 && ft_strlen(flags[0]) == 5)
		unset(input, vault);
	else if (ft_strcmp(flags[0], "env") == 0 && ft_strlen(flags[0]) == 3)
	{
		while (vault->envp[i])
			printf("%s\n", vault->envp[i++]);
	}
	else if (ft_strcmp(flags[0], "exit") == 0 && ft_strlen(flags[0]) == 4)
		exit_ms(vault, 0);
	if(x)
	{
		free_pointer(flags);
		free_input_list(input);
		free_vault(vault);
		exit_ms(vault, 0);
	}
	return ;
}
