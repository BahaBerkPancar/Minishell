#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "minishell.h"
# include "parse.h"

char	*set_path(t_vault *vault, char *input);
int		dollar_count(t_input **input);
void	env_to_export(t_vault *vault);
int		set_variable_type(t_vault *vault, t_input **lst);
t_input	*get_rid_of_dquotes(t_input **list);
t_input	*get_rid_of_squotes(t_input **list);
void	add_after(t_input *head, t_input *new);
void	print_to_env(t_vault *vault, char *var);
void	exit_ms(t_vault *vault, int exit_status);
int		update_or_add_var(char *var, t_vault *vault);
int		real_execute(t_input **input, t_vault *vault);
void	tmp_execute(t_input **input, t_vault *vault, int execute);
void	execute(char *path, char **flags, t_vault *vault);
void	execute_command(t_input **input, char **flags, t_vault *vault);
bool	execute_builtin_in_main(t_input **input, t_vault *vault);

int		count_args(t_input *input);
int		pipe_count(t_input **input);
int		find_char(char *input, char c);
void	replace_variables(t_input **final, t_vault *vault);

t_input	**parse(char *input, t_parse *parse);
t_input	*lstlast(t_input *lst);
t_input	*new_node(char *content);
void	ft_lstprint(t_input *lst);
void	last_node(t_input **lst, t_input *new);
void	delete_node(t_input **head, t_input *to_delete);

char	**get_path(t_vault *vault);
int		set_types(t_vault *vault, t_input **lst);
int		set_quoted_types(t_vault *vault, t_input **lst);
void	free_input_list(t_input **list);

char	*vault_getenv(t_vault *vault, const char *name);

bool	is_main_builtin(const char *cmd);
bool	is_token(char *string);
bool	is_flag(const char *arg);
bool	is_builtin(char *string);
bool	is_executable(t_vault *vault, char *string);

int		ft_strcmp(const char *s1, const char *s2);
void	heredoc(char *delimiter, t_input **final, t_vault *vault, char **flags);

void	closed(int fd, int fd1);
void	set_exit_status(t_vault *vault, int exit_status);

int		pwd(void);
int		cd(char *path, t_vault *vault);
void	echo(char **flags);
int		unset(t_input **final, t_vault *vault);
int		export(t_input **final, t_vault *vault);
void	builtin(t_input **input, char **flags, t_vault *vault, int x);

int		dquote_count(char *input);
int		squote_count(char *input);
char	*doublequote_check(char *temp);
char	*singlequote_check(char *temp);
int		find_dquote_location(char *input);
int		find_squote_location(char *input);
char	*seperate_dquotes(t_input **list, char *input, char *quoted);
char	*seperate_squotes(t_input **list, char *input, char *quoted);

void	free_parse(t_parse *parse);
void	free_vault(t_vault *vault);
void	free_input(t_input *input);
void	free_export(t_vault *vault);
void	free_pointer(char **pointer);

int		signal_handler(int sig);
void	handle_sigint(int sig);

#endif