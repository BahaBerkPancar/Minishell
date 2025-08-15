#include "../include/minishell.h"



char	*handle_quotes(char *input, t_input **list, char *token)
{
	if (ft_strchr(token, '\"'))
	{
		if (doublequote_check(input) == NULL)
			return (NULL);
		input = seperate_dquotes(list, input, doublequote_check(input));
	}
	else if (ft_strchr(token, '\''))
	{
		if (singlequote_check(input) == NULL)
			return (NULL);
		input = seperate_squotes(list, input, singlequote_check(input));
	}
	return (input);
}


int handle_tokens(char *input, t_input **list, t_parse *parse)
{
	int x;

	x = 0;
	
	if (*input == '>' || *input == '<' || *input == '|' || *input == '$')
	{
		x = 1;
		if ((*input == '>' && input[1] == '>') || (*input == '<' && input[1] == '<'))
			x = 2;
		else if (*input == '$' && input[1] == ' ')
			x = 2;
		parse->token = ft_substr(input, 0, x);
		last_node(list, new_node(ft_strdup(parse->token)));
	}
	else
		return (0);
	return (x);
}
int get_input(char *input,  t_parse *parse)
{
	int len;

	len = 0;
	while (input[len] && input[len] != ' ' && input[len] != '>'
		&& input[len] != '<' && input[len] != '|' && input[len] != '$')
		len++;
	parse->token = ft_substr(input, 0, len);
	return (len);
}

t_input	**parse(char *input, t_parse *parse)
{
	t_input	**list;

	list = malloc(sizeof(t_input *));
	*list = NULL;
	while (*input)
	{
		if (*input == ' ')
			input++;
		else if (*input == '>' || *input == '<' || *input == '|' || *input == '$')
			input += handle_tokens(input, list, parse);
		else
		{
			parse->len = get_input(input, parse);
			if (ft_strchr(parse->token, '\"') || ft_strchr(parse->token, '\''))
				input = handle_quotes(input, list, parse->token);
			else
			{
				last_node(list, new_node(ft_strdup(parse->token)));
				input += parse->len;
			}
		}
		free(parse->token);
		parse->token = NULL;
	}
	if(parse->token)
	{
		free(parse->token);
		parse->token = NULL;
	}
	return (free_parse(parse), list);
}
