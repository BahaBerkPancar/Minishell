#include "../include/minishell.h"

t_parse	*start_parse(t_parse *parse)
{
	parse = malloc(sizeof(t_parse));
	parse->x = 1;
	parse->len = 0;
	parse->token = NULL;
	return (parse);
}

char *handle_quotes(char *input, t_input **list, char *token)
{
    char *quoted;
    char *new_input;

    new_input = NULL;
    if (ft_strchr(token, '\"'))
    {
        new_input = seperate_dquotes(list, input,  doublequote_check(input));
    }
    else if (ft_strchr(token, '\''))
    {
        quoted = singlequote_check(input);
        if (quoted == NULL)
            return NULL;
        new_input = seperate_squotes(list, input, quoted);
        free(quoted);
    }
    free(input);
    return new_input;
}


t_input	**parse(char *input)
{
	t_input	**list;
	t_parse	*parse;

	list = malloc(sizeof(t_input *));
	parse = start_parse(NULL);
	*list = NULL;
	while (*input)
	{
		if (*input == ' ')
			input++;
		else if (*input == '>' || *input == '<' || *input == '|' || *input == '$')
		{
			parse->x = 1;
			if ((*input == '$' && input[1] == ' ') || (input[1] == '>' || input[1] == '<'))
				parse->x = 2;
			parse->token = ft_substr(input, 0, parse->x);
			last_node(list, new_node(ft_strdup(parse->token)));
			input += parse->x;
		}
		else
		{
			parse->len = 0;
			while (input[parse->len] && input[parse->len] != ' ' && input[parse->len] != '>'
				&& input[parse->len] != '<' && input[parse->len] != '|' && input[parse->len] != '$')
				parse->len++;
			parse->token = ft_substr(input, 0, parse->len);
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
	return (free_parse(parse), list);
}
