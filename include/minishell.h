#ifndef MINISHELL_H
# define MINISHELL_H

# define READLINE_LIBRARY  // Add this line before including readline

# define minishell main

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>   // Include readline after the define
# include <readline/history.h>    // history.h comes after readline.h
# include <dirent.h>
# include <libft.h>
# include <parse.h>
# include <functions.h>
# include <sys/wait.h>


// int		find_char(char *input, char c);
// char	operations_check(char *input);
// void	ft_lstprint(t_input *lst);
// t_input	*parse(char *input);
// t_input	*new_node(char *content);
// void	last_node(t_input **lst, t_input *new);
// void	set_types(t_input *lst);
// void	doublequote_check(char *input);
// void	singlequote_check(char *input);
// char	**get_path(void);
// bool	is_executable(char *string);
// bool	is_flag(const char *arg);
// bool	is_builtin(char *string);
// bool	is_token(char *string);
// int		ft_strcmp(const char *s1, const char *s2);

#endif
