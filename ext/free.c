#include "../include/minishell.h"

void	free_input(t_input *input)
{
	t_input *tmp;

	while (input)
	{
		tmp = input->next;
		free(input->value);
		free(input);
		input = tmp;
	}
}

void	free_input_list(t_input **list)
{
	if (!list)
		return;
	free_input(*list);
	free(list);
}

void	free_pointer(char **pointer)
{
	int	i;

	i = 0;
	while (pointer[i])
		free(pointer[i++]);
	free(pointer);
}

void	free_export(t_vault *vault)
{
	int	i;

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

void	free_parse(t_parse *parse)
{
	if (parse)
	{
		if(parse->token)
		{
			free(parse->token);
			parse->token = NULL;
		}
		free(parse);
	}
}

void free_vault(t_vault *vault)
{
	if(vault->envp)
		free_pointer(vault->envp);
	if(vault)
		free_export(vault);
	// if(vault->home)
	// free(vault->home);
	if(vault->oldpwd)
		free(vault->oldpwd);
	if(vault->pwd)
		free(vault->pwd);
	if(vault)
		free(vault);
}
