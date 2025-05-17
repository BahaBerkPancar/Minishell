#include <minishell.h>

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

char	**get_path(void)
{
	char	*path_env;

	path_env = getenv("PATH");
	return (ft_split(path_env, ':'));
}

bool	is_executable(char *string)
{
	char	**paths;
	int		i;
	char	*temp;

	i = 0;
	paths = get_path();
	temp = ft_strdup(string);
	if (!ft_strchr(temp, '/'))
	{
		while (paths[i])
		{
			string = ft_strjoin("/", temp);
			string = ft_strjoin(paths[i], string);
			if (access(string, F_OK) == 0)
				break ;
			free(string);
			i++;
		}
	}
	if (access(string, X_OK) == 0)
		return (free(temp), free(paths), true);
	return (free(temp), free(paths), false);
}
