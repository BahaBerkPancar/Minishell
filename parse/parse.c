#include <minishell.h>

t_parse *start_parse(t_parse *parse)
{
	parse = malloc(sizeof(t_parse));
	parse->x = 1;
	parse->len = 0;
	parse->token = NULL;
	return (parse);
}

char	*handle_quotes(char *input, t_input **list, char *token)
{
	if(ft_strchr(token, '\"'))
	{
		if(doublequote_check(input) == NULL)
			return (NULL);
		input = seperate_dquotes(list, input, doublequote_check(input));
	}
	else if(ft_strchr(token, '\''))
	{
		if(singlequote_check(input) == NULL)
			return (NULL);
		input = seperate_squotes(list, input, singlequote_check(input));
	}
	return(input);
}
t_input	**parse(char *input)
{
	t_input **list;
	t_parse *parse;

	list = malloc(sizeof(t_input *));
	parse = NULL;
	parse = start_parse(parse);
	while (*input)
	{
		if (*input == ' ')
			input++;
		else if (*input == '>' || *input == '<' || *input == '|')
		{
			parse->x = 1;
			if(input[1] == '>' || input[1] == '<')
				parse->x = 2;
			parse->token = ft_substr(input, 0, parse->x);
			last_node(list, new_node(parse->token));
			input += parse->x;
		}
		else
		{
			parse->len = 0;
			while (input[parse->len] && input[parse->len] != ' ' && input[parse->len] != '>'
				&& input[parse->len] != '<' && input[parse->len] != '|')
				parse->len++;
			parse->token = ft_substr(input, 0, parse->len);
			if(ft_strchr(parse->token, '\"') || ft_strchr(parse->token, '\''))
				input = handle_quotes(input, list, parse->token);
			else
			{
				last_node(list, new_node(parse->token));
				input += parse->len;
			}
		}
	}
	free(parse);
	return (list);
}
