#include <minishell.h>


char	*seperate_Squotes(t_input **list, char *input, char *quoted)
{
	if(quoted == NULL)
		return (input);
	last_node(list, new_node(quoted));
	if (lstlast(*list))
		lstlast(*list)->is_quoted = true;
	if(ft_strncmp(input, quoted, ft_strlen(quoted)) == 0)
		return (ft_substr(input, ft_strlen(quoted) + 1, ft_strlen(input) - ft_strlen(quoted) - 1));
	else
		return (input);
}

int	Squote_count(char *input)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if(input[i] == '\'')
			count++;
		i++;
	}
	return (count);
}

int	find_Squote_location(char *input)
{
	int i;

	i = 0;
	while (input[i])
	{
		if(input[i] == '\'')
			return (i);
		i++;
	}
	return (0);
}

char	*Singlequote_check(char *input)
{
	int i;
	int j;
	char *temp;

	i = 0;
	temp = input;
	while (Squote_count(temp) > 2)
		temp = ft_substr(temp, 0, ft_strlen(temp) - 1);
	i = find_Squote_location(temp);
	j = find_Squote_location(temp + i + 1) + i + 1;
	while(ft_strchr(ft_substr(temp, j, ft_strlen(temp) - j), ' '))
		temp = ft_substr(temp, 0, ft_strlen(temp) - 1);
	return (temp);
}
