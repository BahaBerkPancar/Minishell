#include <minishell.h>

void set_types_helper(t_input **lst)
{
	t_input *tmp;

	tmp = *lst;
	while(tmp)
	{
		if (tmp->type == NONE)
		{
			if(is_builtin(tmp->value))
				tmp->type = BUILTIN;
			else if(is_flag(tmp->value))
				tmp->type = FLAG;
			else if (!ft_strcmp(tmp->value, ">>"))
			{
				tmp->type = TOKEN;
				tmp->next->type = APPEND_OUTPUT;
			}
			else if (!ft_strcmp(tmp->next->value, "<<"))
			{
				tmp->type = HEREDOC;
				tmp->next->type = TOKEN;
			}
		}
		tmp = tmp->next;
	}

}
void set_types(t_input **lst)
{
	t_input *tmp;	

	tmp = *lst;
	while (tmp)
	{
		if (tmp->type == NONE)
		{
			if (!ft_strcmp(tmp->value, "|"))
				tmp->type = PIPE;
			else if (!ft_strcmp(tmp->value, ">") || !ft_strcmp(tmp->value, ">>"))
			{
				tmp->type = TOKEN;
				tmp->next->type = REDIRECT_OUTPUT;
			}
			else if (!ft_strcmp(tmp->value, "<") || !ft_strcmp(tmp->value, "<<"))
			{
				tmp->type = TOKEN;
				tmp->next->type = REDIRECT_INPUT;
			}
			else if (tmp->is_quoted == false && is_executable(tmp->value))
				tmp->type = COMMAND;
			else
				tmp->type = ARGUMANT;
		}
		tmp = tmp->next;
	}
	set_types_helper(lst);
}
