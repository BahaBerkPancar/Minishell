/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skalkan <skalkan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:49:48 by skalkan           #+#    #+#             */
/*   Updated: 2025/08/23 23:49:49 by skalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute(char *path, char **flags, t_vault *vault)
{
	if (execve(path, flags, vault->envp) == -1)
	{
		free_pointer(flags);
		printf("Command not found\n");
		exit_ms(vault, 127);
	}
	exit(1);
}

char	**build_argv_until_pipe(t_input **node, int i, int count)
{
	t_input	*tmp;
	t_input	*tmp1;
	char	**argv;

	tmp = *node;
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

void	child_process(t_input **input, t_input *tmp, t_vault *vault, int prev_read_end, int pipe_fds[2])
{
	char	**flags;

	flags = NULL;
	if (!has_command_until_pipe(tmp) || tmp->type == ARGUMENT)
	{
		printf("command not found\n");
		redir_execute(&tmp, vault, 0);
		free_input_list(input);
		free_vault(vault);
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		exit(127);
	}
	closed(prev_read_end, 0);
	if (has_next_pipe(tmp))
		dup2(pipe_fds[1], 1);
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	redir_execute(&tmp, vault, 0);
	flags = build_argv_until_pipe(&tmp, 0, 0);
	execute_command(input, flags, vault);
	free_pointer(flags);
}

int	execute_pipe(t_input **input, t_vault *vault, t_input *tmp,
	int prev_read_end)
{
	pid_t	pid;
	int		pipe_fds[2];
	int		status;

	while (tmp)
	{
		pipe(pipe_fds);
		pid = fork();
		if (pid == 0)
			child_process(input, tmp, vault, prev_read_end, pipe_fds);
		else if (pid > 0)
		{
			close(pipe_fds[1]);
			closed(prev_read_end, -1);
			prev_read_end = pipe_fds[0];
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
			execute_pipe(input, vault, *input, -1);
			free_input_list(input);
			free_vault(vault);
			exit(127);
		}
		else
			waitpid(pid, NULL, 0);
	}
	else if (pipe_count(input) == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			if (!has_command_until_pipe(*input) || (*input)->type == ARGUMENT)
			{
				printf("command not found\n");
				redir_execute(input, vault, 0);
				free_input_list(input);
				set_exit_status(vault, 127);
				free_vault(vault);
				exit(127);
			}
			redir_execute(input, vault, 1);
		}
		else
			waitpid(pid, NULL, 0);
	}
	return (1);
}
