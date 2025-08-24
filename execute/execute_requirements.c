/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_requirements.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpancar <bpancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:49:21 by skalkan           #+#    #+#             */
/*   Updated: 2025/08/24 03:42:36 by bpancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**get_flags(t_input **input, char *cmd)
{
	t_input	*tmp;
	int		i;
	int		argc;
	char	**flags;

	i = 0;
	tmp = *input;
	while (tmp && ft_strcmp(tmp->value, cmd) != 0)
		tmp = tmp->next;
	if (!tmp)
		return (NULL);
	argc = count_args(tmp);
	flags = malloc((argc + 2) * sizeof(char *));
	if (!flags)
		return (NULL);
	flags[i++] = ft_strdup(cmd);
	tmp = tmp->next;
	while (tmp && tmp->type != PIPE && tmp->type != TOKEN)
	{
		flags[i++] = ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	flags[i] = NULL;
	return (flags);
}

static int	handle_input_redirect(t_input **input, t_input *tmp, t_vault *vault,
	char **flags)
{
	int	fd;

	fd = open(tmp->value, O_RDONLY);
	if (fd == -1)
	{
		printf("minishell: %s: No such file or directory\n", tmp->value);
		closed(fd, -1);
		cleanup_and_exit(input, flags, vault, 1);
		return (0);
	}
	closed(fd, STDIN_FILENO);
	return (1);
}

static int	handle_output_redirect(t_input **input, t_input *tmp,
	t_vault *vault, char **flags)
{
	int	fd;

	fd = 0;
	if (tmp->type == REDIRECT_OUTPUT)
		fd = open(tmp->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (tmp->type == APPEND_OUTPUT)
		fd = open(tmp->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		printf("minishell: %s: Permission denied\n", tmp->value);
		closed(fd, -1);
		cleanup_and_exit(input, flags, vault, 1);
		return (0);
	}
	closed(fd, STDOUT_FILENO);
	return (1);
}

void	redir_execute(t_input **input, t_vault *vault, int flag, int x)
{
	t_input	*tmp;
	char	**flags;

	tmp = *input;
	flags = NULL;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == 6 && !handle_input_redirect(input, tmp, vault, flags))
			return ;
		else if ((tmp->type == REDIRECT_OUTPUT || tmp->type == APPEND_OUTPUT)
			&& !handle_output_redirect(input, tmp, vault, flags))
			return ;
		else if (tmp->type == TOKEN && ft_strcmp(tmp->value, "<<") == 0
			&& ft_strlen(tmp->value) == 2)
		{
			heredoc(tmp->next->value, input, vault, flags);
			tmp = tmp->next;
		}
		else if ((tmp->type == COMMAND || tmp->type == BUILTIN)
			&& flag == 1 && flag-- && x)
			flags = get_flags(input, tmp->value);
		tmp = tmp->next;
	}
	if (x)
		execute_command(input, flags, vault);
}

void	execute(char *path, char **flags, t_vault *vault)
{
	if (execve(path, flags, vault->envp) == -1)
		cleanup_and_exit(NULL, flags, vault, 127);
}
