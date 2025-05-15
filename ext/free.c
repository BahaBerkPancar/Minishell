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
void free_pointer(char **pointer)
{
	int i;

	i = 0;
	while (pointer[i])
		free(pointer[i++]);
	free(pointer);
}

void free_export(t_vault *vault)
{
	int i;

	if (!vault->export)
		return ;
	i = 0;
	while (vault->export[i])
	{
		free(vault->export[i]);
		vault->export[i] = NULL;
		i++;
	}
	free(vault->export);
	vault->export = NULL;
}
