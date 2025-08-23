/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpancar <bpancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 00:01:24 by skalkan           #+#    #+#             */
/*   Updated: 2025/08/24 00:46:08 by bpancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	pipe_count(t_input **input)
{
	t_input	*tmp;
	int		count;

	tmp = *input;
	count = 0;
	while (tmp)
	{
		if (tmp->type == PIPE)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

int	dollar_count(t_input **input)
{
	t_input	*tmp;
	int		count;

	tmp = *input;
	count = 0;
	while (tmp)
	{
		if (ft_strcmp(tmp->value, "$") == 0)
			count++;
		tmp = tmp->next;
	}
	return (count);
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
