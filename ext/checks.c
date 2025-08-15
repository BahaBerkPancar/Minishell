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
	if (ft_strcmp(string, "echo") == 0 && ft_strlen(string) == 4)
		return (true);
	if(ft_strcmp(string, "clear") == 0 && ft_strlen(string) == 5)
		return (true);
	if (ft_strcmp(string, "cd") == 0 && ft_strlen(string) == 2)
		return (true);
	if (ft_strcmp(string, "pwd") == 0 && ft_strlen(string) == 3)
		return (true);
	if (ft_strcmp(string, "export") == 0 && ft_strlen(string) == 6)
		return (true);
	if (ft_strcmp(string, "unset") == 0 && ft_strlen(string) == 5)
		return (true);
	if (ft_strcmp(string, "env") == 0 && ft_strlen(string) == 3)
		return (true);
	if (ft_strcmp(string, "exit") == 0 && ft_strlen(string) == 4)
		return (true);
	return (false);
}

char	**get_path(void)
{
	char	*path_env;

	path_env = getenv("PATH");
	return (ft_split(path_env, ':'));
}
char *ft_strjoin_free(char *s1, const char *s2)
{
	char *joined = ft_strjoin(s1, s2);
	free(s1);
	return joined;
}
void free_split(char **arr)
{
	int i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	free(arr);
}

bool is_executable(char *string)
{
	char	**paths;
	char	*full_path;
	int		i;

	i = 0;
	if (!string || !*string)
		return (false);
	if (ft_strchr(string, '/'))
		return (access(string, X_OK) == 0);
	paths = get_path();
	if (!paths)
		return (false);
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin_free(full_path, string);
		if (!full_path)
			return (free_split(paths), false);
		if (access(full_path, X_OK) == 0)
			return (free(full_path), free_split(paths), true);
		free(full_path);
		i++;
	}
	return (free_split(paths), false);
}
bool is_executable2(char *string)
{
	char	**paths;
	char	*full_path;
	int		i;

	i = 0;
	if (!string || !*string)
		return (false);
	if (ft_strchr(string, '/'))
		return (access(string, X_OK) == 0);
	paths = get_path();
	if (!paths)
		return (false);
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin_free(full_path, string);
		printf("Checking path: %s\n", full_path);
		if (!full_path)
			return (free_split(paths), false);
		if (access(full_path, X_OK) == 0)
			return (free(full_path), free_split(paths), true);
		free(full_path);
		i++;
	}
	return (free_split(paths), false);
}