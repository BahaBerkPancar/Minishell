#include <minishell.h>

void free_input(t_input *input)
{
	while(input)
	{
		free(input->value);
		input = input->next;
	}
	free(input);
}