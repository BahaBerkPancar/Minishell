/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpancar <bpancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 01:05:52 by bpancar           #+#    #+#             */
/*   Updated: 2025/08/24 01:07:09 by bpancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*get_env_value(const char *name, char **envp)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(name);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

static void	handle_exit_code(t_input **final, t_input **tmp)
{
	t_input	*to_delete;

	free((*tmp)->next->value);
	(*tmp)->next->value = ft_itoa(*get_exit_status_code());
	to_delete = *tmp;
	*tmp = (*tmp)->next;
	delete_node(final, to_delete);
}

static void	handle_env_variable(t_input **final, t_input **tmp, t_vault *vault)
{
	char	*env_value;
	t_input	*to_delete;

	env_value = get_env_value((*tmp)->next->value, vault->envp);
	if (env_value)
	{
		free((*tmp)->next->value);
		(*tmp)->next->value = ft_strdup(env_value);
	}
	else
		delete_node(final, (*tmp)->next);
	to_delete = *tmp;
	*tmp = (*tmp)->next;
	delete_node(final, to_delete);
}

void	handle_variable(t_input **final, t_input **tmp, t_vault *vault)
{
	if (ft_strcmp((*tmp)->value, "$") == 0 && ft_strlen((*tmp)->value) == 1)
	{
		if ((*tmp)->next && ft_strcmp((*tmp)->next->value, "?") == 0
			&& ft_strlen((*tmp)->next->value) == 1)
			handle_exit_code(final, tmp);
		else
			handle_env_variable(final, tmp, vault);
	}
	else
		*tmp = (*tmp)->next;
}
