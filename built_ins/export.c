#include "../include/minishell.h"


int	add_env_var(char *var, t_vault *vault)
{
	int count = 0;
	while (vault->envp && vault->envp[count])
		count++;

	char **new_envp = malloc(sizeof(char *) * (count + 2));
	if (!new_envp)
		return (1);

	for (int i = 0; i < count; i++)
		new_envp[i] = vault->envp[i];

	new_envp[count] = ft_strdup(var);
	new_envp[count + 1] = NULL;
	free(vault->envp);
	vault->envp = new_envp;
	return (0);
}


void print_to_env(t_vault *vault, char *var)
{
    char *key;
    int i = 0;

    key = ft_strchr(var, '=');
    if (!key)
        return;

    if (vault->envp)
    {
        while (vault->envp[i])
        {
            if (ft_strncmp(vault->envp[i], var, ft_strlen(var) - ft_strlen(key)) == 0)
            {
                free(vault->envp[i]);
                vault->envp[i] = ft_strdup(var);
                return;
            }
            i++;
        }
    }
    add_env_var(var, vault);
}



static int	is_valid_identifier(char *str)
{
	if (!str || !*str)
		return (0);
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	str++;
	while (*str && *str != '=')
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

static char	**sort_export(char **envp)
{
	int		i;
	int		j;
	char	*tmp;
	int		len;

	if (!envp)
		return (NULL);
	len = 0;
	while (envp[len])
		len++;
	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (ft_strcmp(envp[j], envp[j + 1]) > 0)
			{
				tmp = envp[j];
				envp[j] = envp[j + 1];
				envp[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	return (envp);
}

static void	print_export(t_vault *vault)
{
	int	i;

	i = 0;
	while (vault->export && vault->export[i])
	{
		printf("declare -x %s\n", vault->export[i]);
		i++;
	}
}

static char	**add_to_export(char *var, t_vault *vault)
{
	char	**new_export;
	int		i;
	int		len;

	len = 0;
	while (vault->export && vault->export[len])
		len++;
	new_export = malloc(sizeof(char *) * (len + 2));
	if (!new_export)
		return (NULL);
	i = -1;
	while (++i < len)
	{
		new_export[i] = ft_strdup(vault->export[i]);
		if (!new_export[i])
			return (free_pointer(new_export), NULL);
	}
	new_export[i] = ft_strdup(var);
	if (!new_export[i])
		return (free_pointer(new_export), NULL);
	new_export[i + 1] = NULL;
	return (new_export);
}

int	update_or_add_var(char *var, t_vault *vault)
{
	char	**new_export;
	int		i;

	i = 0;
	while (vault->export && vault->export[i])
	{
		if (ft_strncmp(vault->export[i], var, ft_strchr(var, '=') - var + 1) == 0
			|| ft_strncmp(vault->export[i], var, ft_strlen(vault->export[i])) == 0)
		{
			free(vault->export[i]);
			vault->export[i] = ft_strdup(var);
			print_to_env(vault, var);
			return (0);
		}
		i++;
	}
	new_export = add_to_export(var, vault);
	if (!new_export)
		return (1);
	free_export(vault);
	vault->export = new_export;
	sort_export(vault->export);
	print_to_env(vault, var);
	return (0);
}

int	export(t_input **final, t_vault *vault)
{
	t_input	*tmp;
	int		status;

	tmp = *final;
	if (!tmp->next)
		return (print_export(vault), 0);
	tmp = tmp->next;
	status = 0;
	while (tmp)
	{
		if (!is_valid_identifier(tmp->value))
		{
			printf("minishell: export: '%s': not a valid identifier\n", tmp->value);
			status = 1;
		}
		else if (update_or_add_var(tmp->value, vault))
			status = 1;
		tmp = tmp->next;
	}
	return (status);
}

void	env_to_export(t_vault *vault)
{
	int		i;
	char	**new_export;

	i = 0;
	while (vault->envp[i])
	{
		if (ft_strchr(vault->envp[i], '=') != NULL)
		{
			new_export = add_to_export(vault->envp[i], vault);
			if (new_export)
			{
				if (vault->export)
					free_export(vault);
				vault->export = sort_export(new_export);
			}
		}
		i++;
	}
}
