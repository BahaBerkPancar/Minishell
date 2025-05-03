#include <minishell.h>

int minishell(int ac, char **av, char *envp[])
{
	(void) envp;
	(void) av;
	char *a;
	t_input *final;
	
	if(ac != 1)
		exit(0);
	while (1)
	{
		a = readline("\nwrite something\n");
		if (!a)
			break;
		// printf("%d\n", is_executable(a));
		// Doublequote_check(a);
		// Singlequote_check(a);
		if(ft_strcmp(a, "pwd") == 0)
			pwd();
		else if(ft_strcmp(a, "clear") == 0)
			clear();
		else
		{
			final = parse(a);
			ft_lstprint(final);
			// set_types(final);
			// free(a);
		}
		add_history(a);
		free(a);
	}
	// signal(SIGINT, SIG_DFL); 
	// signal(SIGQUIT, SIG_DFL);x
}
