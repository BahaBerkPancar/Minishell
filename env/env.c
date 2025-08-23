/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpancar <bpancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:44:33 by skalkan           #+#    #+#             */
/*   Updated: 2025/08/24 01:07:35 by bpancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	replace_variables(t_input **final, t_vault *vault)
{
	t_input	*tmp;

	tmp = *final;
	while (tmp)
	{
		if (tmp->value[0] == '$' && ft_strcmp(tmp->value, "$") != 0)
		{
			add_after(tmp, new_node(ft_strdup(tmp->value + 1)));
			tmp->next->type = VARIABLE;
			tmp->next->is_variable = true;
			free(tmp->value);
			tmp->value = ft_strdup("$");
		}
		if (tmp && tmp->next)
			handle_variable(final, &tmp, vault);
		else
			tmp = tmp->next;
	}
}

void	cleanup_and_exit(t_input **input, char **flags, t_vault *vault,
	int exit_status)
{
	free_pointer(flags);
	free_input_list(input);
	free_vault(vault);
	set_exit_status_code(exit_status);
	exit(*get_exit_status_code());
}
