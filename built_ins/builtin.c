#include <minishell.h>

void	builtin(t_input **input, char **flags, t_vault *vault)
{
	int		i;

	i = 0;
	if(ft_strcmp(flags[0], "echo") == 0)
		echo(flags + 1);
	else if(ft_strcmp(flags[0], "cd") == 0)
	{
		if(flags[1] || !flags[2])
			cd(flags[1], vault);
		else if(!flags[1])
			cd("", vault);
		else
			printf("minishell: cd: too many arguments\n");
	}
	else if(ft_strcmp(flags[0], "pwd") == 0)
	{
		if(!flags[1])
			pwd();
		else
			printf("minishell: pwd: too many arguments\n");
	}
	else if(ft_strcmp(flags[0], "export") == 0)
		export(input, vault);
	else if(ft_strcmp(flags[0], "unset") == 0)
		unset(input, vault);
	else if(ft_strcmp(flags[0], "clear") == 0)
		clear();
	else if (ft_strcmp(flags[0], "env") == 0)
	{
		while (vault->envp[i])
			printf("%s\n", vault->envp[i++]);
	}
	else if (ft_strcmp(flags[0], "exit") == 0)
		exit_ms(vault, 0);
	// exit_ms(vault, 1);
}
