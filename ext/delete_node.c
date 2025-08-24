/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpancar <bpancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:51:01 by skalkan           #+#    #+#             */
/*   Updated: 2025/08/24 04:01:26 by bpancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	delete_node(t_input **head, t_input *remove)
{
	t_input	*prev;

	if (!head || !*head || !remove)
		return ;
	if (*head == remove)
	{
		*head = remove->next;
		free(remove->value);
		free(remove);
		return ;
	}
	prev = *head;
	while (prev && prev->next != remove)
		prev = prev->next;
	if (!prev)
		return ;
	prev->next = remove->next;
	free(remove->value);
	free(remove);
}

void	add_after(t_input *head, t_input *new)
{
	if (!head || !new)
		return ;
	new->next = head->next;
	head->next = new;
}

void	free_input_list(t_input **list)
{
	if (!list)
		return ;
	free_input(*list);
	free(list);
}
