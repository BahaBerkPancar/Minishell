/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skalkan <skalkan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 00:03:55 by skalkan           #+#    #+#             */
/*   Updated: 2025/08/24 00:09:42 by skalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_n_option(char *arg, int *index)
{
	int	check;
	int	j;

	check = 0;
	j = 1;
	if (!arg || arg[0] != '-')
		return (0);
	while (arg[j] == 'n')
	{
		check = 1;
		j++;
	}
	*index = j;
	return (check && arg[j] == '\0');
}

static void	print_args(char **arg, int start)
{
	int	i;

	i = start;
	while (arg[i])
	{
		printf("%s", arg[i]);
		if (arg[i + 1])
			printf(" ");
		i++;
	}
}

void	echo(char **arg)
{
	int	i;
	int	j;
	int	n_flag;

	if (!arg[1])
	{
		printf("\n");
		return ;
	}
	j = 1;
	n_flag = is_n_option(arg[1], &j);
	i = 1 + n_flag;
	print_args(arg, i);
	if ((arg[1] && !n_flag) || (arg[1] && n_flag && arg[1][j] != '\0'))
		printf("\n");
}
