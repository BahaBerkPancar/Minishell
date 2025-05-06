# ifndef PARSE_H
# define PARSE_H

#include <stdbool.h>

typedef enum {
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
    ARGUMANT,
    TOKEN
} InputType;


typedef struct s_input
{
    bool is_quoted;
    bool is_doublequoted;
	InputType type;
    char *value;
	struct s_input *next;
}		t_input;

typedef struct s_parse
{
    char *token;
	int len;
	int x;
}	t_parse;

typedef struct s_vault
{
    char **envp;
    char *oldpwd;
    char *pwd;
    char *home;
}	t_vault;

t_input **parse(char *input);

#endif