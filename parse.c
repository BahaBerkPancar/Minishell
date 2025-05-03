#include <minishell.h>

char	*seperate_quotes(t_input **list, char *input, char *quoted)
{
	(void)list;
	(void)input;
	(void)quoted;
	return (NULL);
}

t_input	*parse(char *input)
{
	t_input *list = NULL;
	char *token;
	int len;
	int x;

	x = 0;
	while (*input)
	{
		if (*input == ' ')
			input++;
		else if (*input == '>' || *input == '<' || *input == '|')
		{
			x = 1;
			if(input[1] == '>' || input[1] == '<')
				x = 2;
			token = ft_substr(input, 0, x);
			last_node(&list, new_node(token));
			input += x;
		}
		else
		{
			len = 0;
			while (input[len] && input[len] != ' ' && input[len] != '>' && input[len] != '<' && input[len] != '|')
				len++;
			token = ft_substr(input, 0, len);
			if(ft_strchr(token, '\"'))
			{
				if(Doublequote_check(input) == NULL)
					return (NULL);
				input = seperate_quotes(&list, input, Doublequote_check(input));
				// printf("input = %s\n", input);
			}
			else
			{
				last_node(&list, new_node(token));
				input += len;
			}
		}
	}
	return (list);
}

int	quote_count(char *input)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if(input[i] == '\"' || input[i] == '\'')
			count++;
		i++;
	}
	return (count);
}

char	*Doublequote_check(char *input)
{
	int i;
	int j;
	char *doublequoted;
	int x;
	char *temp;
	
	x = 0;
	i = 0;
	temp = input;
	while (quote_count(temp) > 2)
		temp = ft_substr(temp, 0, ft_strlen(temp) - 1);
	while (temp[i])
	{
		if(temp[i] == '\"')
		{
			while(ft_strchr(ft_substr(temp, 0, i), ' '))
			{
				i--;
				temp++;
			}
			j = i + 1;
			while(temp[j] != '\"' && temp[j])
				j++;
			if(temp[j] == '\"')
			{
				while(ft_strchr(ft_substr(temp, j, ft_strlen(temp) - x), ' '))
					x++;
				doublequoted = ft_substr(temp, 0, ft_strlen(temp) - x);
				return (doublequoted);
			}
			else
				return((void)printf("UNCLOSED DOUBLE QUOTE\n"),  NULL);
		}
		i++;
	}
	return (NULL);
}

void	Singlequote_check(char *input)
{
	int i;
	int j;
	char *singlequoted;
	
	i = 0;
	printf("============\n");
	while (input[i])
	{
		if (input[i] == '\'')
		{
			j = i + 1;
			while (input[j] && input[i] != input[j])
				j++;
			if(input[j] == '\'')
			{
				singlequoted = ft_substr(input, i, j - i + 1);
				printf("singlequoted = %s\n", singlequoted);
				i = j + 1;
			}
			else
				return((void)printf("UNCLOSED SINGLE QUOTE\n"));
		}
		i++;
	}
}


