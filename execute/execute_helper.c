/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skalkan <skalkan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:48:57 by skalkan           #+#    #+#             */
/*   Updated: 2025/08/23 23:49:08 by skalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute_command(t_input **input, char **flags, t_vault *vault)
{
	if (flags && is_builtin(flags[0]))
		builtin(input, flags, vault, 1);
	else if (flags && is_executable(vault, flags[0]) && !is_builtin(flags[0]))
		execute(set_path(vault, flags[0]), flags, vault);
	else
	{
		free_pointer(flags);
		free_input_list(input);
		set_exit_status(vault, 127);
		free_vault(vault);
		exit(127);
	}
}

bool	execute_builtin_in_main(t_input **input, t_vault *vault)
{
	t_input	*tmp;
	char	**flags;
	int		stdin_copy;
	int		stdout_copy;

	if (!input || !*input)
		return (false);
	tmp = *input;
	while (tmp && tmp->type != COMMAND && tmp->type != BUILTIN)
		tmp = tmp->next;
	if (!tmp || !is_main_builtin(tmp->value))
		return (false);
	flags = get_flags(input, tmp->value);
	if (!flags)
		return (false);
	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	redir_execute(input, vault, 0);
	builtin(input, flags, vault, 0);
	dup2(stdin_copy, STDIN_FILENO);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdin_copy);
	close(stdout_copy);
	free_pointer(flags);
	return (true);
}

void	open_pipe(int **fd, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		fd[i] = (int *)malloc(sizeof(int) * 2);
		pipe(fd[i]);
		i++;
	}
}

bool	has_next_pipe(t_input *node)
{
	while (node)
	{
		if (node->type == PIPE)
			return (true);
		node = node->next;
	}
	return (false);
}

bool	has_command_until_pipe(t_input *node)
{
	while (node)
	{
		if (node->value && node->value[0] == '|')
			break ;
		if (node->value && (node->type == COMMAND || node->type == BUILTIN))
			return (true);
		node = node->next;
	}
	return (false);
}
