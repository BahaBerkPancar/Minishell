#ifndef FUNCTIONS_H
#define	FUNCTIONS_H

# include <minishell.h>
# include <parse.h>

int		find_char(char *input, char c);
char	operations_check(char *input);
void	ft_lstprint(t_input *lst);
t_input	**parse(char *input);
t_input	*new_node(char *content);
void	last_node(t_input **lst, t_input *new);
void	set_types(t_input **lst);
char	**get_path(void);
bool	is_executable(char *string);
bool	is_flag(const char *arg);
bool	is_builtin(char *string);
bool	is_token(char *string);
int		ft_strcmp(const char *s1, const char *s2);
char	*Doublequote_check(char *input);
t_input	*lstlast(t_input *lst);
int		pwd(void);
int		clear(void);
char	*seperate_Dquotes(t_input **list, char *input, char *quoted);
char	*seperate_Squotes(t_input **list, char *input, char *quoted);
int		Dquote_count(char *input);
int		Squote_count(char *input);
int		find_Dquote_location(char *input);
int		find_Squote_location(char *input);
char	*Singlequote_check(char *input);
#endif