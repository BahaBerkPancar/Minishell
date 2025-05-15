#include <minishell.h>

t_vault	*init_vault(char **envp)
{
	t_vault	*vault;

	vault = malloc(sizeof(t_vault));
	vault->envp = envp;
	vault->export = NULL;
	env_to_export(vault);
	vault->oldpwd = getcwd(NULL, 0);
	vault->pwd = getcwd(NULL, 0);
	vault->home = getenv("HOME");
	return (vault);
}

int	set_necesery_type(t_input **final, t_vault *vault)
{
	if (!set_types(final))
		return ((void)printf("SYNTAX ERROR\n")
			, free_input(*final), 0);
	if (!*final)
		return (0);
	get_rid_of_dquotes(final);
	replace_variables(final, vault);
	get_rid_of_squotes(final);
	if (!set_quoted_types(final))
		return ((void)printf("SYNTAX ERROR\n")
			, free_input(*final), 0);
	// if ((*final)->type == ARGUMANT)
	// 	return ((void)printf("command not found\n")
			// , free_input(*final), 0);
	return (1);
}

int	minishell(int ac, char **av, char *envp[])
{
	char	*a;
	t_input	**final;
	t_vault	*vault;

	(void) av;
	if (ac != 1)
		return ((void)printf("NO ARGUMENTS ALLOWED\n"), exit(0), 0);
	vault = init_vault(envp);
	while (1)
	{
		a = readline("MINISHELL : ");
		if (!a || !*a)
			continue ;
		add_history(a);
		if (!tmp_builtin(a, vault))
			continue ;
		else
		{
			final = parse(a);
			if (!set_necesery_type(final, vault))
				continue ;
			free(a);
			// ft_lstprint(*final);
			real_execute(final, vault);
		}
	}
	free_input(*final);
	free(vault);
}
