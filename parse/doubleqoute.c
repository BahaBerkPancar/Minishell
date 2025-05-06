#include <minishell.h>

t_input *get_rid_of_dquotes(t_input **list)
{
	t_input *tmp;
	char *final;
	char *remaining;
	int i;

	tmp = *list;
	while(tmp)
	{
		final = ft_strdup("");
		if(ft_strchr(tmp->value, '\"'))
			tmp->value = ft_strtrim(tmp->value, "\"");
		if(ft_strchr(tmp->value, '\"'))
		{
			remaining = tmp->value;
			while(*remaining)
			{
				i = 0;
				while(remaining[i] != '\"' && remaining[i])
					i++;
				final = ft_strjoin(final, ft_substr(remaining, 0, i));
				remaining = ft_substr(remaining, i + 1, ft_strlen(remaining) - i);
			}
			tmp->value = final;
		}
		tmp = tmp->next;
	}
	return (*list);
}

char	*seperate_dquotes(t_input **list, char *input, char *quoted)
{
	if(quoted == NULL)
		return (input);
	last_node(list, new_node(quoted));
	if (lstlast(*list))
		lstlast(*list)->is_doublequoted = true;
	if(ft_strncmp(input, quoted, ft_strlen(quoted)) == 0)
		return (ft_substr(input, ft_strlen(quoted) + 1, ft_strlen(input) - ft_strlen(quoted) - 1));
	else
		return (input);
}

int	dquote_count(char *input)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if(input[i] == '\"')
			count++;
		i++;
	}
	return (count);
}

int	find_dquote_location(char *input)
{
	int i;

	i = 0;
	while (input[i])
	{
		if(input[i] == '\"')
			return (i);
		i++;
	}
	return (0);
}

char	*doublequote_check(char *input)
{
	int i;
	int j;
	char *temp;

	i = 0;
	temp = input;
	while (dquote_count(temp) > 2)
		temp = ft_substr(temp, 0, ft_strlen(temp) - 1);
	i = find_dquote_location(temp);
	j = find_dquote_location(temp + i + 1) + i + 1;
	while(ft_strchr(ft_substr(temp, j, ft_strlen(temp) - j), ' '))
		temp = ft_substr(temp, 0, ft_strlen(temp) - 1);
	return (temp);
}
