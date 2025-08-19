#include "../include/minishell.h"
#include <stdlib.h>
#include <string.h>

t_vault *init_vault(char **envp, int count, int i)
{
	t_vault *vault;

	vault = malloc(sizeof(t_vault));
	if (!vault)
		return (NULL);
	vault->export = NULL;
	vault->oldpwd = getcwd(NULL, 0);
	vault->pwd = getcwd(NULL, 0);
	vault->home = getenv("HOME");
	while (envp && envp[count])
		count++;
	vault->envp = malloc(sizeof(char *) * (count + 1));
	if (!vault->envp)
		return (free(vault), NULL);
	while (++i < count)
	{
		vault->envp[i] = strdup(envp[i]);
		if (!vault->envp[i])
			return(free_vault(vault), NULL);
	}
	vault->envp[count] = NULL;
	update_or_add_var("SHELL=minishell", vault);
	env_to_export(vault);
	vault->exit_status = -1;
	return (vault);
}

t_parse	*start_parse(t_parse *parse)
{
	parse = malloc(sizeof(t_parse));
	parse->x = 1;
	parse->len = 0;
	parse->token = NULL;
	return (parse);
}

int	set_necesery_type(t_input **final, t_vault *vault)
{
	if (!set_types(vault, final))
		return ((void)printf("SYNTAX ERROR\n"),free_input_list(final), set_exit_status(vault, 258), 0);
	if (!*final)
		return (0);
	get_rid_of_dquotes(final);
	replace_variables(final, vault);
	// ft_lstprint(*final);
	get_rid_of_squotes(final);
	if (!set_quoted_types(vault, final))
		return ((void)printf("SYNTAX ERROR\n"), set_exit_status(vault, 258), 0);
	if (*final && (*final)->type == ARGUMENT && (*final)->is_variable == false)
		return ((void)printf("command not found\n"),  free_input_list(final), set_exit_status(vault, 127), 0);
	// ft_lstprint(*final);
	return (1);
}

int main(int ac, char **av, char *envp[])
{
	char    *a;
	t_input **final;
	t_vault *vault;

	if (ac != 1 || !av)
		return ((void)printf("NO ARGUMENTS ALLOWED\n"), exit(0), 0);
	vault = init_vault(envp, 0, -1);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	while (1)
	{
		g_signal_exit = 0;
		a = readline("MINISHELL : ");
		if (!a)
			return(free(a), free_vault(vault), exit(0), 0);
		add_history(a);
		final = parse(a, start_parse(NULL));
		if (!final || !*final)
			continue;
		if (!set_necesery_type(final, vault))
			continue;
		real_execute(final, vault);
		if(final)
			free_input_list(final);
		// if(vault->exit_status != -1)
		//     exit(vault->exit_status);
	}
	rl_clear_history();
	return 0;
}
