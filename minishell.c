#include "../include/minishell.h"
#include <stdlib.h>
#include <string.h>

t_vault *init_vault(char **envp)
{
    t_vault *vault;
    int count = 0;
    int i = -1;

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
    return (vault);
}


int	set_necesery_type(t_input **final, t_vault *vault)
{						 
	if (!set_types(final))
		return ((void)printf("SYNTAX ERROR\n"), free_input(*final), free(final), exit_code(vault, 258), 0);
	if (!*final)
		return (0);
	get_rid_of_dquotes(final);
	replace_variables(final, vault);
	get_rid_of_squotes(final);
	if (!set_quoted_types(final))
		return ((void)printf("SYNTAX ERROR\n"), exit_code(vault, 258), 0);
	if (*final && (*final)->type == ARGUMANT && (*final)->is_variable == false)
		return ((void)printf("command not found\n"), free_input_list(final), exit_code(vault, 127), 0);
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
    vault = init_vault(envp);
    while (1)
    {
        a = readline("MINISHELL : ");
        if (!a || !*a)
        {
            free(a);
            continue;
        }
        add_history(a);
        final = parse(a);  // parse takes ownership of a and frees it internally
        if (!final)
            continue;
        if (!set_necesery_type(final, vault)) 
            continue;
        real_execute(final, vault);

        // free final list here as needed
    }
    rl_clear_history();
    // free vault and final here if needed
    return 0;
}
