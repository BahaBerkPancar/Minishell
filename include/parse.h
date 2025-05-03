# ifndef PARSE_H
# define PARSE_H

#include <stdbool.h>

typedef enum {
    PIPE,
    COMMAND,
    FILE_INPUT,
    HEREDOC,
    REDIRECT_OUTPUT,
    REDIRECT_INPUT,
    APPEND_OUTPUT
} InputType;


typedef struct s_input
{
    bool is_quoted;
    bool is_doublequoted;
	InputType type;
    char *value;
	struct s_input *next;
}		t_input;

t_input *parse(char *input);

#endif