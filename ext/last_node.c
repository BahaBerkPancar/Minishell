/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skalkan <skalkan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:53:38 by skalkan           #+#    #+#             */
/*   Updated: 2025/08/23 23:53:51 by skalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_input	*lstlast(t_input *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	last_node(t_input **lst, t_input *new)
{
	t_input	*temp;

	if (!new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	temp = lstlast(*lst);
	temp->next = new;
}
