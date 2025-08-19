#include "../include/minishell.h"

bool	is_token(char *string)
{
	if (ft_strcmp(string, "|") == 0)
		return (true);
	if (ft_strcmp(string, ">") == 0)
		return (true);
	if (ft_strcmp(string, "<") == 0)
		return (true);
	if (ft_strcmp(string, ">>") == 0)
		return (true);
	if (ft_strcmp(string, "<<") == 0)
		return (true);
	return (false);
}

bool	is_flag(const char *arg)
{
	size_t	len;

	if (!arg)
		return (false);
	len = ft_strlen(arg);
	if (len < 2)
		return (false);
	if (arg[0] == '-')
	{
		if (arg[1] == '-' && len > 2)
			return (true);
		else if (arg[1] != '-')
			return (true);
	}
	return (false);
}

bool	is_builtin(char *string)
{
	if (ft_strcmp(string, "echo") == 0)
		return (true);
	if (ft_strcmp(string, "cd") == 0)
		return (true);
	if (ft_strcmp(string, "pwd") == 0)
		return (true);
	if (ft_strcmp(string, "export") == 0)
		return (true);
	if (ft_strcmp(string, "unset") == 0)
		return (true);
	if (ft_strcmp(string, "env") == 0)
		return (true);
	if (ft_strcmp(string, "exit") == 0)
		return (true);
	return (false);
}

char	*vault_getenv(t_vault *vault, const char *name)
{
	int		i;
	size_t	name_len;
	char	*entry;

	if (!vault || !name || !vault->envp)
		return (NULL);
	name_len = ft_strlen(name);
	i = 0;
	while (vault->envp[i])
	{
		entry = vault->envp[i];
		if (!entry)
		{
			i++;
			continue ;
		}
		if (ft_strncmp(entry, name, name_len) == 0 && entry[name_len] == '=')
			return (entry + name_len + 1);
		i++;
	}
	return (NULL);
}

char	**get_path(t_vault *vault)
{
	char	*path_env;

	path_env = vault_getenv(vault, "PATH");
	if (!path_env || !*path_env)
		return (NULL);
	return (ft_split(path_env, ':'));
}
