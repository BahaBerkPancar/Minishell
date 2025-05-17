#include "minishell.h"

static int	is_valid_identifier(char *str)
{
	if (!str || !*str)
		return (0);
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	str++;
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

static void	remove_from_array(char **str, int i)
{
	free(str[i]);
	while (str[i + 1])
	{
		str[i] = str[i + 1];
		i++;
	}
	str[i] = NULL;
}

static int	unset_variable(char *var, t_vault *vault)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(var);
	while (vault->export && vault->export[++i])
	{
		if (ft_strncmp(vault->export[i], var, len) == 0
			&& (vault->export[i][len] == '=' || vault->export[i][len] == '\0'))
		{
			remove_from_array(vault->export, i);
			break ;
		}
	}
	i = -1;
	while (vault->envp && vault->envp[++i])
	{
		if (ft_strncmp(vault->envp[i], var, len) == 0
			&& (vault->envp[i][len] == '=' || vault->envp[i][len] == '\0'))
		{
			remove_from_array(vault->envp, i);
			break ;
		}
	}
	return (0);
}

int	unset(t_input **final, t_vault *vault)
{
	t_input	*tmp;
	int		status;

	tmp = (*final)->next;
	status = 0;
	while (tmp)
	{
		if (!is_valid_identifier(tmp->value))
		{
			printf("minishell: unset: '%s': not a valid identifier\n",
				tmp->value);
			status = 1;
		}
		else
			unset_variable(tmp->value, vault);
		tmp = tmp->next;
	}
	return (status);
}
