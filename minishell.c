#include <minishell.h>

int minishell(int ac, char **av, char *envp[])
{
	(void) envp;
	(void) av;
	char *a;
	t_input **final;
	
	if(ac != 1)
	{
		printf("NO ARGUMENTS ALLOWED\n");
		exit(0);
	}
	while (1)
	{
		a = readline("\nwrite something\n");
		if (!a)
			break;
		// printf("%d\n", is_executable(a));
		if(ft_strcmp(a, "pwd") == 0)
			pwd();
		else if(ft_strcmp(a, "clear") == 0)
			clear();
		else
		{
			final = parse(a);
			set_types(final);// it doesnt set the last node type
			ft_lstprint((*final));
		}
		add_history(a);
		free(a);
	}
}
