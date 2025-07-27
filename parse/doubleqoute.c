#include "../include/minishell.h"

t_input	*get_rid_of_dquotes(t_input **list)
{
	t_input	*tmp;
	char	*final;
	char	*remaining;
	int		i;

	tmp = *list;
	while (tmp)
	{
		final = ft_strdup("");
		if (ft_strchr(tmp->value, '\"'))
			tmp->value = ft_strtrim(tmp->value, "\"");
		if (ft_strchr(tmp->value, '\"'))
		{
			remaining = tmp->value;
			while (*remaining)
			{
				i = 0;
				while (remaining[i] != '\"' && remaining[i])
					i++;
				final = ft_strjoin(final, ft_substr(remaining, 0, i));
				remaining = ft_substr(remaining, i + 1, ft_strlen(remaining) - i);
			}
			if (ft_strlen(final) > 0)//////////////
				tmp->value = final;
			else
				tmp->value = ft_strdup("\0");
		}
		tmp = tmp->next;
		free(final);
	}
	return (*list);
}

char	*seperate_dquotes(t_input **list, char *input, char *quoted)
{
	char *result;

	if (quoted == NULL)
		return (input);
	result = ft_strdup(quoted);
	last_node(list, new_node(ft_strdup(result)));
	free(result);
	if (lstlast(*list))
		lstlast(*list)->is_doublequoted = true;
	if (ft_strncmp(input, quoted, ft_strlen(quoted)) == 0)
		result = ft_substr(input, ft_strlen(quoted) + 1, ft_strlen(input) - ft_strlen(quoted) - 1);
	else
		result = ft_strdup(input);
	return (free(quoted), result);
}

int	dquote_count(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == '\"')
			count++;
		i++;
	}
	return (count);
}

int	find_dquote_location(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\"')
			return (i);
		i++;
	}
	return (0);
}

char	*doublequote_check(char *input)
{
	int		i;
	int		j;
	char	*temp;
	char 	*tmp;

	i = 0;
	temp = input;
	while (dquote_count(temp) > 2)
		temp = ft_substr(temp, 0, ft_strlen(temp) - 1);
	i = find_dquote_location(temp);
	j = find_dquote_location(temp + i + 1) + i + 1;
	tmp = ft_substr(temp, j, ft_strlen(temp) - j);
	while (ft_strchr(tmp, ' '))
		temp = ft_substr(temp, 0, ft_strlen(temp) - 1);
	free(tmp);
	return (temp);
}

// void	replace_empty_dquotes(t_input **list)
// {
// 	t_input *tmp;

// 	tmp = *list;
// 	while (tmp)
// 	{
// 		if (!tmp->value || !tmp->value[0])
// 		{
// 			printf("here\n");
// 			tmp->value = ft_strdup("");
// 		}
// 		tmp = tmp->next;
// 	}
// }