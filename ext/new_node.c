#include "../include/minishell.h"

t_input	*new_node(char *content)
{
	t_input	*str;

	str = malloc(sizeof(t_input));
	if (!str)
		return (NULL);
	str->value = content;
	str->type = NONE;
	str->is_quoted = false;
	str->is_doublequoted = false;
	str->is_variable = false;
	str->next = NULL;
	return (str);
}
