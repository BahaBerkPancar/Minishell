/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skalkan <skalkan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:52:28 by skalkan           #+#    #+#             */
/*   Updated: 2025/08/23 23:52:29 by skalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_lstprint(t_input *lst)
{
	t_input	*tmp;

	tmp = lst;
	while (tmp != NULL)
	{
		printf("(%s)->", tmp->value);
		tmp = tmp->next;
	}
	printf("NULL\n");
	while (lst != NULL)
	{
		printf("(%u)->", lst->type);
		lst = lst->next;
	}
	printf("NULL\n");
}
