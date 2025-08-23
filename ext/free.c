/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skalkan <skalkan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:51:55 by skalkan           #+#    #+#             */
/*   Updated: 2025/08/24 00:14:30 by skalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_input(t_input *input)
{
	t_input	*tmp;

	while (input)
	{
		tmp = input->next;
		free(input->value);
		free(input);
		input = tmp;
	}
}

void	free_pointer(char **pointer)
{
	int	i;

	i = 0;
	while (pointer && pointer[i])
	{
		free(pointer[i]);
		i++;
	}
	free(pointer);
}

void	free_export(t_vault *vault)
{
	int	i;

	if (!vault || !vault->export)
		return ;
	i = 0;
	while (vault->export[i])
	{
		free(vault->export[i]);
		vault->export[i] = NULL;
		i++;
	}
	free(vault->export);
	vault->export = NULL;
}

void	free_parse(t_parse *parse)
{
	if (parse)
	{
		if (parse->token)
		{
			free(parse->token);
			parse->token = NULL;
		}
		free(parse);
	}
}

void	free_vault(t_vault *vault)
{
	if (!vault)
		return ;
	if (vault->envp)
		free_pointer(vault->envp);
	free_export(vault);
	if (vault->oldpwd)
		free(vault->oldpwd);
	if (vault->pwd)
		free(vault->pwd);
	free(vault);
}
