/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpancar <bpancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:59:31 by skalkan           #+#    #+#             */
/*   Updated: 2025/08/24 01:16:13 by bpancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*handle_quotes(char *input, t_input **list, char *token)
{
	char	*quoted;
	char	*result;

	result = NULL;
	if (ft_strchr(token, '\"'))
	{
		quoted = doublequote_check(ft_strdup(input));
		if (quoted == NULL)
			return (NULL);
		result = seperate_dquotes(list, input, quoted);
		free(quoted);
	}
	else if (ft_strchr(token, '\''))
	{
		quoted = singlequote_check(ft_strdup(input));
		if (quoted == NULL)
			return (NULL);
		result = seperate_squotes(list, input, quoted);
		free(quoted);
	}
	if (!result)
		return (free(input), NULL);
	return (result);
}

int	handle_tokens(char *input, t_input **list, t_parse *parse)
{
	int		x;
	t_input	*node;

	x = 0;
	if (*input == '>' || *input == '<' || *input == '|' || *input == '$')
	{
		x = 1;
		if ((*input == '>' && input[1] == '>')
			|| (*input == '<' && input[1] == '<'))
			x = 2;
		else if (*input == '$' && input[1] == ' ')
			x = 2;
		parse->token = ft_substr(input, 0, x);
		if (!parse->token)
			return (x);
		node = new_node(ft_strdup(parse->token));
		if (!node)
			return (free(parse->token), x);
		last_node(list, node);
	}
	else
		return (0);
	return (x);
}

int	get_input(char *input, t_parse *parse)
{
	int	len;

	len = 0;
	while (input[len] && input[len] != ' ' && input[len] != '>'
		&& input[len] != '<' && input[len] != '|' && input[len] != '$')
		len++;
	parse->token = ft_substr(input, 0, len);
	return (len);
}

t_input	**init_input_list(void)
{
	t_input	**list;

	list = malloc(sizeof(t_input *));
	if (!list)
		return (NULL);
	*list = NULL;
	return (list);
}

t_input	**parse(char *input, t_parse *parse)
{
	t_input	**list;

	list = init_input_list();
	while (*input)
	{
		if (*input == ' ')
			input++;
		else if (*input == '>' || *input == '<'
			|| *input == '|' || *input == '$')
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
	return (free_parse(parse), list);
}
