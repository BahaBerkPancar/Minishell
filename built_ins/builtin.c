/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpancar <bpancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:39:06 by skalkan           #+#    #+#             */
/*   Updated: 2025/08/24 03:29:45 by bpancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	handle_cd(char **flags, t_vault *vault)
{
	if (flags[1] && !flags[2])
		cd(flags[1], vault);
	else if (!flags[1])
		cd("", vault);
	else
		printf("minishell: cd: too many arguments\n");
}

static void	handle_pwd(char **flags)
{
	if (!flags[1])
		pwd();
	else
		printf("minishell: pwd: too many arguments\n");
}

static void	handle_env(t_vault *vault)
{
	int	i;

	i = 0;
	while (vault->envp[i])
	{
		printf("%s\n", vault->envp[i]);
		i++;
	}
}

void	handle_exit(char **flags, t_input **input, t_vault *vault)
{
	printf("exit\n");
	if (flags[1] && flags[2])
	{
		printf("minishell: exit: too many arguments\n");
		set_exit_status_code(1);
		return ;
	}
	else if (flags[1])
	{
		if (is_number(flags[1]))
			cleanup_and_exit(input, flags, vault, ft_atoi(flags[1]) % 256);
		else
		{
			printf("minishell: exit: numeric argument required\n");
			cleanup_and_exit(input, flags, vault, 255);
		}
	}
	else
		cleanup_and_exit(input, flags, vault, *get_exit_status_code());
}

void	builtin(t_input **input, char **flags, t_vault *vault, int x)
{
	if (ft_strcmp(flags[0], "echo") == 0 && ft_strlen(flags[0]) == 4)
		echo(flags);
	else if (ft_strcmp(flags[0], "cd") == 0 && ft_strlen(flags[0]) == 2)
		handle_cd(flags, vault);
	else if (ft_strcmp(flags[0], "pwd") == 0 && ft_strlen(flags[0]) == 3)
		handle_pwd(flags);
	else if (ft_strcmp(flags[0], "export") == 0 && ft_strlen(flags[0]) == 6)
		export(input, vault);
	else if (ft_strcmp(flags[0], "unset") == 0 && ft_strlen(flags[0]) == 5)
		unset(input, vault);
	else if (ft_strcmp(flags[0], "env") == 0 && ft_strlen(flags[0]) == 3
		&& !flags[1])
		handle_env(vault);
	else if (ft_strcmp(flags[0], "exit") == 0 && ft_strlen(flags[0]) == 4)
		handle_exit(flags, input, vault);
	if (x)
		cleanup_and_exit(input, flags, vault, 0);
}
