#include <minishell.h>
#include <sys/wait.h>

t_vault *init_vault(char **envp)
{
	t_vault *vault;

	vault = malloc(sizeof(t_vault));
	vault->envp = envp;
	vault->oldpwd = getcwd(NULL, 0);
	vault->pwd = getcwd(NULL, 0);
	vault->home = getenv("HOME");
	return (vault);
}

int minishell(int ac, char **av, char *envp[])
{
	(void) av;
	char *a;
	t_input **final;
	t_vault *vault;
	int pid;

	vault = init_vault(envp);
	if(ac != 1)
	{
		printf("NO ARGUMENTS ALLOWED\n");
		exit(0);
	}
	while (1)
	{
		a = readline("MINISHELL > ");
		if (!a)
			break;
		add_history(a);
		if(!tmp_builtin(a, vault))
			continue;
		else
		{
			final = parse(a);
			get_rid_of_dquotes(final);
			get_rid_of_squotes(final);
			set_types(final);// it doesnt set the last node type
			// ft_lstprint((*final));
			pid = fork();
			if(pid == 0)
				tmp_execute(final, vault);
			else
				waitpid(pid, NULL, 0);
		}
		free(a);
	}
	// rl_clear_history();
	free_input(*final);
	free(vault);
}
