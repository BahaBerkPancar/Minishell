#ifndef FUNCTIONS_H
#define	FUNCTIONS_H

# include <minishell.h>
# include <parse.h>

int		tmp_builtin(char *input, t_vault *vault);
void	add_after(t_input *head, t_input *new);
int		real_execute(t_input **input, t_vault *vault);
void	tmp_execute(t_input **input, t_vault *vault);
void	execute(char *path, char **flags, t_vault *vault);
char	*set_path(char *input);
t_input *get_rid_of_dquotes(t_input **list);
t_input *get_rid_of_squotes(t_input **list);
int		set_variable_type(t_input **lst);
int	dollar_count(t_input **input);

t_input	*final_new_node(char *content, int type, bool is_quoted, bool is_doublequoted);

void delete_node(t_input **head, t_input *to_delete);

int	pipe_count(t_input **input);
char *get_env_value(const char *name, char **envp);
void replace_variables(t_input **final, t_vault *vault);
int		cd(char *path, t_vault *vault);
int		find_char(char *input, char c);
char	operations_check(char *input);
void	ft_lstprint(t_input *lst);
t_input	**parse(char *input);
t_input	*new_node(char *content);
void	last_node(t_input **lst, t_input *new);
int		set_types(t_input **lst);
int		set_quoted_types(t_input **lst);
char	**get_path(void);
bool	is_executable(char *string);
bool	is_flag(const char *arg);
bool	is_builtin(char *string);
bool	is_token(char *string);
int		ft_strcmp(const char *s1, const char *s2);
char	*doublequote_check(char *input);
t_input	*lstlast(t_input *lst);
int		pwd(void);
int		clear(void);
char	*seperate_dquotes(t_input **list, char *input, char *quoted);
char	*seperate_squotes(t_input **list, char *input, char *quoted);
int		dquote_count(char *input);
int		squote_count(char *input);
int		find_dquote_location(char *input);
int		find_squote_location(char *input);
char	*singlequote_check(char *input);
void	free_parse(t_parse *parse);
void	free_vault(t_vault *vault);
void	free_input(t_input *input);
#endif