/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpancar <bpancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:49:48 by skalkan           #+#    #+#             */
/*   Updated: 2025/08/24 03:42:49 by bpancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**build_argv_until_pipe(t_input **node, t_input *tmp, int i, int count)
{
	t_input	*tmp1;
	char	**argv;

	tmp1 = tmp;
	while (tmp1 && tmp1->type != PIPE)
	{
		if (tmp1->type == COMMAND || tmp1->type == ARGUMENT || tmp1->type
			== FLAG || tmp1->type == VARIABLE || tmp1->type == BUILTIN)
			count++;
		tmp1 = tmp1->next;
	}
	argv = malloc(sizeof(char *) * (count + 1));
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == COMMAND || tmp->type == ARGUMENT || tmp->type
			== FLAG || tmp->type == VARIABLE || tmp->type == BUILTIN)
			argv[i++] = ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	argv[i] = NULL;
	if (tmp && tmp->type == PIPE)
		tmp = tmp->next;
	*node = tmp;
	return (argv);
}

void	child_process(t_input **input, t_input *tmp, t_vault *vault,
		int pipe_fds[2])
{
	char	**flags;

	flags = NULL;
	if (!has_command_until_pipe(tmp) || tmp->type == ARGUMENT)
	{
		printf("command not found\n");
		redir_execute(&tmp, vault, 0, 0);
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		cleanup_and_exit(input, NULL, vault, 127);
	}
	closed(vault->prev_read_end, 0);
	if (has_next_pipe(tmp))
		dup2(pipe_fds[1], 1);
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	redir_execute(&tmp, vault, 0, 0);
	flags = build_argv_until_pipe(&tmp, tmp, 0, 0);
	execute_command(input, flags, vault);
	free_pointer(flags);
}

int	execute_pipe(t_input **input, t_vault *vault, t_input *tmp)
{
	pid_t	pid;
	int		pipe_fds[2];
	int		status;

	while (tmp)
	{
		pipe(pipe_fds);
		pid = fork();
		if (pid == 0)
			child_process(input, tmp, vault, pipe_fds);
		else if (pid > 0)
		{
			close(pipe_fds[1]);
			closed(vault->prev_read_end, -1);
			vault->prev_read_end = pipe_fds[0];
			while (tmp && tmp->type != PIPE)
				tmp = tmp->next;
			if (tmp)
				tmp = tmp->next;
		}
	}
	while (wait(&status) > 0)
		;
	return (0);
}

int	one_command_execute(t_input **input, t_vault *vault)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (!has_command_until_pipe(*input) || (*input)->type == ARGUMENT)
		{
			printf("command not found\n");
			redir_execute(input, vault, 0, 0);
			cleanup_and_exit(input, NULL, vault, 127);
		}
		redir_execute(input, vault, 1, 1);
	}
	else if (pid > 0)
		wait_child(pid);
	return (1);
}

int	real_execute(t_input **input, t_vault *vault)
{
	pid_t	pid;

	if (!pipe_count(input) && execute_builtin_in_main(input, vault))
		return (1);
	if (pipe_count(input))
	{
		pid = fork();
		if (pid == 0)
		{
			execute_pipe(input, vault, *input);
			cleanup_and_exit(input, NULL, vault, 127);
		}
		else
			wait_child(pid);
	}
	else if (pipe_count(input) == 0)
		one_command_execute(input, vault);
	return (1);
}
