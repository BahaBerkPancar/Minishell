/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpancar <bpancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:51:46 by skalkan           #+#    #+#             */
/*   Updated: 2025/08/24 01:12:09 by bpancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	find_char(char *input, char c)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == c)
			break ;
		i++;
	}
	return (i);
}

int	type_check(t_input *lst)
{
	while (lst)
	{
		if (lst->type == NONE)
			return (0);
		lst = lst->next;
	}
	return (1);
}
