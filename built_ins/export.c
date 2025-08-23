#include "../include/minishell.h"

char	**add_to_export(char *var, t_vault *vault)
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
	i = 0;
	while (i < len)
	{
		new_export[i] = ft_strdup(vault->export[i]);
		if (!new_export[i])
			return (free_pointer(new_export), NULL);
		i++;
	}
	new_export[i] = ft_strdup(var);
	if (!new_export[i])
		return (free_pointer(new_export), NULL);
	new_export[i + 1] = NULL;
	return (new_export);
}

static int	update_existing_var(char *var, t_vault *vault)
{
	int		i;
	char	*eq;

	eq = ft_strchr(var, '=');
	i = 0;
	while (vault->export && vault->export[i])
	{
		if (ft_strncmp(vault->export[i], var, eq - var + 1) == 0
			|| ft_strncmp(vault->export[i], var,
				ft_strlen(vault->export[i])) == 0)
		{
			free(vault->export[i]);
			vault->export[i] = ft_strdup(var);
			print_to_env(vault, var);
			return (1);
		}
		i++;
	}
	return (0);
}

int	update_or_add_var(char *var, t_vault *vault)
{
	char	**new_export;

	if (update_existing_var(var, vault))
		return (0);
	new_export = add_to_export(var, vault);
	if (!new_export)
		return (1);
	free_export(vault);
	vault->export = new_export;
	sort_export(vault->export);
	print_to_env(vault, var);
	return (0);
}

static int	export_args(t_input *tmp, t_vault *vault)
{
	int	status;

	status = 0;
	while (tmp)
	{
		if (tmp->type != PIPE && tmp->type != TOKEN
			&& !is_valid_identifier_export(tmp->value))
		{
			printf("minishell: export: '%s': not a valid identifier\n",
				tmp->value);
			status = 1;
		}
		else if (update_or_add_var(tmp->value, vault))
			status = 1;
		tmp = tmp->next;
	}
	return (status);
}

int	export(t_input **final, t_vault *vault)
{
	t_input	*tmp;

	tmp = *final;
	if ((tmp->next && (tmp->next->type == PIPE
				|| tmp->next->type == TOKEN)) || !tmp->next)
	{
		print_export(vault);
		return (0);
	}
	tmp = tmp->next;
	return (export_args(tmp, vault));
}
