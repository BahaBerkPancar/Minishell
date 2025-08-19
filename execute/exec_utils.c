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

char *remove_slash(const char *path)
{
	int		len;
	char	*copy;

	if (!path)
		return (NULL);
	copy = ft_strdup(path);
	if (!copy)
		return (NULL);
	len = ft_strlen(copy);
	if (len > 1 && copy[len - 1] == '/')
		copy[len - 1] = '\0';
	return (copy);
}


#include <sys/stat.h>
bool is_executable(t_vault *vault, char *string)
{
	char		**paths;
	char		*full_path;
	char		*tmp;
	int			i;
	struct stat	st;

	i = -1;
	if (!string || !*string)
		return (false);
	tmp = remove_slash(string);
	if (!tmp)
		return (false);
	if (ft_strchr(tmp, '/'))
	{
		if (stat(tmp, &st) == 0 && S_ISREG(st.st_mode) && access(tmp, X_OK) == 0)
			return (free(tmp), true);
	}
	paths = get_path(vault);
	if (!paths)
		return (free(tmp), false);
	while (paths[++i])
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin_free(full_path, tmp);
		if (!full_path)
			return (free_split(paths), free(tmp), false);
		if (stat(full_path, &st) == 0 && S_ISREG(st.st_mode) && access(full_path, X_OK) == 0)
			return (free(tmp), free_split(paths), free(full_path), true);
		free(full_path);
	}
	return (free_split(paths), free(tmp), false);
}
