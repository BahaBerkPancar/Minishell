#include <minishell.h>


void set_types(t_input **lst)
{
	t_input *tmp;	

	tmp = *lst;
	while (tmp->next)
	{
		if (tmp->type == NONE)
		{
			if (tmp->value[0] == '|')
				tmp->type = PIPE;
			else if (tmp->value[0] == '>')
			{
				tmp->type = TOKEN;
				tmp->next->type = REDIRECT_OUTPUT;
			}
			else if (tmp->next->value[0] == '<')
			{
				tmp->type = TOKEN;
				tmp->next->type = REDIRECT_INPUT;
			}
			else
				tmp->type = COMMAND;
		}
		tmp = tmp->next;
	}
}