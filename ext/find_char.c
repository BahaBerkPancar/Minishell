/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skalkan <skalkan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:51:46 by skalkan           #+#    #+#             */
/*   Updated: 2025/08/23 23:51:47 by skalkan          ###   ########.fr       */
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
