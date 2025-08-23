#include "../include/minishell.h"

int	add_env_var(char *var, t_vault *vault)
{
	int		count;
	char	**new_envp;
	int		i;

	count = 0;
	while (vault->envp && vault->envp[count])
		count++;
	new_envp = malloc(sizeof(char *) * (count + 2));
	if (!new_envp)
		return (1);
	i = 0;
	while (i < count)
	{
		new_envp[i] = vault->envp[i];
		i++;
	}
	new_envp[count] = ft_strdup(var);
	new_envp[count + 1] = NULL;
	free(vault->envp);
	vault->envp = new_envp;
	return (0);
}

void	print_to_env(t_vault *vault, char *var)
{
	char	*key;
	int		i;

	key = ft_strchr(var, '=');
	if (!key)
		return ;
	i = 0;
	while (vault->envp && vault->envp[i])
	{
		if (ft_strncmp(vault->envp[i], var,
				ft_strlen(var) - ft_strlen(key)) == 0)
		{
			free(vault->envp[i]);
			vault->envp[i] = ft_strdup(var);
			return ;
		}
		i++;
	}
	add_env_var(var, vault);
}

int	is_valid_identifier_export(char *str)
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

char	**sort_export(char **envp)
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
	i = -1;
	while (++i < len - 1)
	{
		j = -1;
		while (++j < len - i - 1)
		{
			if (ft_strcmp(envp[j], envp[j + 1]) > 0)
			{
				tmp = envp[j];
				envp[j] = envp[j + 1];
				envp[j + 1] = tmp;
			}
		}
	}
	return (envp);
}

void	print_export(t_vault *vault)
{
	int	i;

	i = 0;
	while (vault->export && vault->export[i])
	{
		printf("declare -x %s\n", vault->export[i]);
		i++;
	}
}
