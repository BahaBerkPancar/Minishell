#include "../include/minishell.h"

char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}

void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	free(arr);
}

bool	is_executable(t_vault *vault, char *string)
{
	char	**paths;
	char	*full_path;
	int		i;

	i = 0;
	if (!string || !*string)
		return (false);
	if (ft_strchr(string, '/') && access(string, X_OK) == 0)
		return (true);
	paths = get_path(vault);
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
