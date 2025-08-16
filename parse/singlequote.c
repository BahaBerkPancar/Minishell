#include "../include/minishell.h"

// static char	*remove_single_quotes(char *str)
// {
// 	char	*final;
// 	char	*remaining;
// 	char	*temp;
// 	char	*joined;
// 	int		i;

// 	final = ft_strdup("");
// 	remaining = str;
// 	while (*remaining)
// 	{
// 		i = 0;
// 		while (remaining[i] != '\'' && remaining[i])
// 			i++;
// 		temp = ft_substr(remaining, 0, i);
// 		joined = ft_strjoin(final, temp);
// 		free(temp);
// 		free(final);
// 		final = joined;
// 		if (remaining[i])
// 			i++;
// 		temp = remaining;
// 		remaining = ft_strdup(remaining + i);
// 		free(temp);
// 	}
// 	return (final);
// }

// t_input	*get_rid_of_squotes(t_input **list)
// {
// 	t_input	*tmp;
// 	char	*new_value;

// 	tmp = *list;
// 	while (tmp)
// 	{
// 		if (ft_strchr(tmp->value, '\''))
// 		{
// 			new_value = remove_single_quotes(tmp->value);
// 			// free(tmp->value);
// 			tmp->value = new_value;
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (*list);
// }

t_input	*get_rid_of_squotes(t_input **list)
{
	t_input	*tmp;
	char	*final;
	char	*remaining;
	int		i;

	tmp = *list;
	while (tmp)
	{
		final = ft_strdup("");
		if (ft_strchr(tmp->value, '\''))
			tmp->value = ft_strtrim(tmp->value, "'");
		if (ft_strchr(tmp->value, '\''))
		{
			remaining = tmp->value;
			while (*remaining)
			{
				i = 0;
				while (remaining[i] != '\'' && remaining[i])
					i++;
				final = ft_strjoin(final, ft_substr(remaining, 0, i));
				remaining = ft_substr(remaining, i + 1, ft_strlen(remaining) - i);
			}
			if (ft_strlen(final) > 0)
				tmp->value = final;
			else
				tmp->value = ft_strdup("\0");
		}
		tmp = tmp->next;
		free(final);
	}
	return (*list);
}

char	*seperate_squotes(t_input **list, char *input, char *quoted)
{
	char *result;

	if (!quoted || ft_strlen(quoted) == 0)
	{
		last_node(list, new_node(ft_strdup("''")));
		return (ft_strdup(input + 2));
	}

	if (quoted == NULL)
		return (input);
	result = ft_strdup(quoted);
	last_node(list, new_node(ft_strdup(result)));
	free(result);
	if (lstlast(*list))
		lstlast(*list)->is_quoted = true;
	if (ft_strncmp(input, quoted, ft_strlen(quoted)) == 0)
		result = ft_substr(input, ft_strlen(quoted) + 1, ft_strlen(input) - ft_strlen(quoted) - 1);
	else
		result = ft_strdup(input);
	return (result);
}

int	squote_count(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			count++;
		i++;
	}
	return (count);
}

int	find_squote_location(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			return (i);
		i++;
	}
	return (0);
}

char	*singlequote_check(char *temp)
{
	int		i;
	int 	j;
	char 	*tmp;
	char	*old_tmp;

	while (squote_count(temp) > 2)
	{
		old_tmp = temp;
		temp = ft_substr(old_tmp, 0, ft_strlen(old_tmp) - 1);
		free(old_tmp);
	}
	i = find_squote_location(temp);
	j = find_squote_location(temp + i + 1) + i + 1;
	tmp = ft_substr(temp, j, ft_strlen(temp) - j);
	while (ft_strchr(tmp, ' '))
	{
		free(tmp);
		old_tmp = temp;
		temp = ft_substr(old_tmp, 0, ft_strlen(old_tmp) - 1);
		free(old_tmp);
		tmp = ft_substr(temp, j, ft_strlen(temp) - j);
	}
	if (!temp || !*temp)
		return (free(tmp), free(temp), ft_strdup(""));
	return (free(tmp), temp);
}
