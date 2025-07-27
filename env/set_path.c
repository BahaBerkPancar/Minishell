#include "../include/minishell.h"

char	*set_path(char *input)
{
	char	*path;
	char	*tmp;
	char	**paths;
	int		i;

	if (ft_strchr(input, '/'))
		return (input);
	path = getenv("PATH");
	paths = ft_split(path, ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		tmp = ft_strjoin(tmp, input);
		if (access(tmp, F_OK) == 0)
		{
			free(paths[i]);
			return (tmp);
		}
		free(tmp);
		i++;
	}
	return (NULL);
}
