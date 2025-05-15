#include <minishell.h>

static int set_token_type(t_input **lst, char *value, InputType type)
{
	t_input *tmp;

	tmp = *lst;
	while(tmp)
	{
		if(tmp->next && !ft_strcmp(tmp->next->value, value) && !ft_strcmp(tmp->value, "$"))
		{
			tmp->type = TOKEN;
			// if(ft_strcmp(tmp->value, "$") != 0)
			// {
			tmp->next->type = VARIABLE;
			tmp->next->is_variable = true;
			// }
		}
		if(!ft_strcmp(tmp->value, value) && tmp->type == NONE)
		{
			tmp->type = TOKEN;
			if(tmp->next && !is_token(tmp->next->value) && ft_strcmp(tmp->next->value, "$") != 0)
				tmp->next->type = type;
			else if(!tmp->next || ft_strcmp(tmp->next->value, "$") != 0)
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

static int set_types_helper(t_input **lst)
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
				if(!set_token_type(lst, tmp->value, APPEND_OUTPUT))
					return (0);
			}
			else if (!ft_strcmp(tmp->value, "<<"))
			{
				if(!set_token_type(lst, tmp->value, HEREDOC))
					return (0);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}
int	set_types(t_input **lst)
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
				if(ft_strcmp(tmp->value, ">"))
					;
				else if(!set_token_type(lst, tmp->value, REDIRECT_OUTPUT))
					return (0);
			}
			else if (!ft_strcmp(tmp->value, "<") || !ft_strcmp(tmp->value, "<<"))
			{
				if(ft_strcmp(tmp->value, "<"))
					;
				else if(!set_token_type(lst, tmp->value, REDIRECT_INPUT))
					return (0);
			}
			else if(tmp->next && !ft_strcmp(tmp->value, "$"))
			{
				if(!set_token_type(lst, tmp->next->value, VARIABLE))
					return (0);
			}
			else if (tmp->is_quoted == false && is_executable(tmp->value))
				tmp->type = COMMAND;
			else
				tmp->type = ARGUMANT;
		}
		tmp = tmp->next;
	}
	return(set_types_helper(lst));
}

int set_quoted_types(t_input **lst)
{
	t_input *tmp;

	tmp = *lst;
	while(tmp)
	{
		if(tmp->type == ARGUMANT || tmp->type == VARIABLE)
		{
			if(tmp->is_variable == true)
			{
				if(!set_variable_type(lst))
					return (0);
			}
			else if(tmp->is_quoted == true || tmp->is_doublequoted == true)
			{
				if(is_executable(tmp->value))
					tmp->type = COMMAND;
				else
					tmp->type = ARGUMANT;
			}
			else
				tmp->type = ARGUMANT;
		}
		tmp = tmp->next;
	}
	return (1);
}

int	set_variable_type(t_input **lst)
{
	t_input *tmp;

	tmp = *lst;
	while(tmp)
	{
		if(tmp->type == TOKEN && tmp->next->is_variable == true)
		{
			if(!ft_strcmp(tmp->value, ">") || !ft_strcmp(tmp->value, ">>"))
				tmp->next->type = REDIRECT_OUTPUT;
			else if(!ft_strcmp(tmp->value, "<") || !ft_strcmp(tmp->value, "<<"))
				tmp->next->type = REDIRECT_INPUT;
		}
		else if(tmp->is_variable == true && tmp->type == VARIABLE)
		{
			if(is_executable(tmp->value) && tmp->is_quoted == false)
				tmp->type = COMMAND;
			else
				tmp->type = ARGUMANT;
		}
		tmp = tmp->next;
	}
	return (1);
}
