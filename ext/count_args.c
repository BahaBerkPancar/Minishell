/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skalkan <skalkan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:50:55 by skalkan           #+#    #+#             */
/*   Updated: 2025/08/23 23:50:56 by skalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_args(t_input *input)
{
	int		count;
	t_input	*tmp;

	count = 0;
	tmp = input->next;
	while (tmp && tmp->type != PIPE && tmp->type != TOKEN)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}
