#include "../include/minishell.h"

static char	*get_env_value(const char *name, char **envp)
{
	int	len;
	int	i;

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

static void	handle_variable(t_input **final, t_input **tmp, t_vault *vault)
{
	char		*env_value;
	t_input		*to_delete;

	if (ft_strcmp((*tmp)->value, "$") == 0 && ft_strlen((*tmp)->value) == 1)
	{
		env_value = get_env_value((*tmp)->next->value, vault->envp);
		if (env_value)
		{
			free((*tmp)->next->value);
			(*tmp)->next->value = ft_strdup(env_value);
		}
		else
		{
			to_delete = (*tmp)->next;
			(*tmp)->next = to_delete->next;
			delete_node(final, to_delete);
		}
		to_delete = *tmp;
		*tmp = (*tmp)->next;
		delete_node(final, to_delete);
	}
	else
		*tmp = (*tmp)->next;
}

void	replace_variables(t_input **final, t_vault *vault)
{
	t_input	*tmp;

	tmp = *final;
	while (tmp)
	{
		if (tmp->value[0] == '$' && ft_strcmp(tmp->value, "$") != 0)
		{
			add_after(tmp, new_node(ft_strdup(tmp->value + 1)));
			tmp->next->type = VARIABLE;
			tmp->next->is_variable = true;
			free(tmp->value);
			tmp->value = ft_strdup("$");
		}
		if (tmp && tmp->next)
			handle_variable(final, &tmp, vault);
		else
			tmp = tmp->next;
	}
}
