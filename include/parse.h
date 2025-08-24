/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpancar <bpancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 00:02:32 by skalkan           #+#    #+#             */
/*   Updated: 2025/08/24 03:39:16 by bpancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdbool.h>

extern int	g_signal_exit;

typedef enum input_type{
	NONE,
	PIPE,
	COMMAND,
	FILE_INPUT,
	HEREDOC,
	REDIRECT_OUTPUT,
	REDIRECT_INPUT,
	APPEND_OUTPUT,
	BUILTIN,
	FLAG,
	ARGUMENT,
	TOKEN,
	VARIABLE
}	t_InputType;

typedef struct s_input
{
	bool			is_quoted;
	bool			is_doublequoted;
	bool			is_variable;
	t_InputType		type;
	char			*value;
	struct s_input	*next;
}		t_input;

typedef struct s_parse
{
	char	*token;
	int		len;
	int		x;
}	t_parse;

typedef struct s_vault
{
	char	**export;
	char	**envp;
	char	*oldpwd;
	char	*pwd;
	char	*home;
	int		prev_read_end;
}	t_vault;

typedef struct s_exec
{
	int	pipe_fds[2];
	int	prev_read_end;
}	t_exec;

#endif