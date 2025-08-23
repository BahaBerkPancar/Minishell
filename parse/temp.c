/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skalkan <skalkan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 00:01:24 by skalkan           #+#    #+#             */
/*   Updated: 2025/08/24 00:01:25 by skalkan          ###   ########.fr       */
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
