#include <minishell.h>

char *get_env_value(const char *name, char **envp)
{
    int len;
	int i;

	i = 0;
	len = ft_strlen(name);
    while (envp[i])
    {
        if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
            return (envp[i] + len + 1);
		i++;
    }
    return (NULL);
}

void replace_variables(t_input **final, t_vault *vault)
{
	t_input *tmp;

	tmp = *final;
	while (tmp)
	{
        if(tmp->next)
        {
            if(ft_strcmp(tmp->value, "$") == 0)
            {
                tmp->next->value = get_env_value(tmp->next->value, vault->envp);
                if (tmp->next->value == NULL)
                    delete_node(final, tmp->next);
                delete_node(final, tmp);
                tmp->type = ARGUMANT;
            }
		}
		tmp = tmp->next;
	}
}
