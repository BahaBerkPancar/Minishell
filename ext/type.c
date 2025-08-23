#include "../include/minishell.h"

static int	set_token_type(t_input **lst, char *value, t_InputType type)
{
	t_input	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (tmp->next && !ft_strcmp(tmp->next->value, value)
			&& !ft_strcmp(tmp->value, "$"))
		{
			tmp->type = TOKEN;
			tmp->next->type = VARIABLE;
			tmp->next->is_variable = true;
		}
		if (!ft_strcmp(tmp->value, value) && tmp->type == NONE)
		{
			tmp->type = TOKEN;
			if (tmp->next && !is_token(tmp->next->value)
				&& ft_strcmp(tmp->next->value, "$") != 0)
				tmp->next->type = type;
			else if (!tmp->next || ft_strcmp(tmp->next->value, "$") != 0)
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	type_check(t_input *lst)
{
	while (lst)
	{
		if (lst->type == NONE)
			return (0);
		lst = lst->next;
	}
	return (1);
}

static int	set_builtin_redirect_type(t_input **lst)
{
	t_input	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (tmp->type == NONE)
		{
			if (is_builtin(tmp->value))
				tmp->type = BUILTIN;
			else if (is_flag(tmp->value))
				tmp->type = FLAG;
			else if (!ft_strcmp(tmp->value, ">>")
				&& !set_token_type(lst, tmp->value, APPEND_OUTPUT))
				return (0);
			else if (!ft_strcmp(tmp->value, "<<")
				&& !set_token_type(lst, tmp->value, HEREDOC))
				return (0);
			else if (!is_builtin(tmp->value) && ft_strcmp(tmp->value, "<<")
				&& ft_strcmp(tmp->value, ">>") && ft_strcmp(tmp->value, "|"))
				tmp->type = ARGUMENT;
		}
		tmp = tmp->next;
	}
	return (type_check(*lst));
}

int	set_types(t_vault *vault, t_input **lst)
{
	t_input	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (tmp->type == NONE)
		{
			if (!ft_strcmp(tmp->value, "|") && tmp->next
				&& ft_strcmp(tmp->next->value, "|"))
				tmp->type = PIPE;
			else if (!ft_strcmp(tmp->value, ">")
				&& !set_token_type(lst, tmp->value, REDIRECT_OUTPUT))
				return ( 0);
			else if (!ft_strcmp(tmp->value, "<")
				&& !set_token_type(lst, tmp->value, REDIRECT_INPUT))
				return (0);
			else if (tmp->next && !ft_strcmp(tmp->value, "$")
				&& !set_token_type(lst, tmp->next->value, VARIABLE))
				return (0);
			else if (tmp->is_quoted == false && is_executable(vault, tmp->value))
				tmp->type = COMMAND;
		}
		tmp = tmp->next;
	}
	return (set_builtin_redirect_type(lst));
}

int	set_quoted_types(t_vault *vault, t_input **lst)
{
	t_input	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (tmp->type == ARGUMENT || tmp->type == VARIABLE)
		{
			if (tmp->is_variable && !set_variable_type(vault, lst))
				return (0);
			else if (tmp->is_quoted || tmp->is_doublequoted || !tmp->is_variable)
			{
				if (is_executable(vault, tmp->value))
					tmp->type = COMMAND;
				else
					tmp->type = ARGUMENT;
			}
			else if (!tmp->is_variable)
				tmp->type = ARGUMENT;
		}
		tmp = tmp->next;
	}
	return (1);
}

int	set_variable_type(t_vault *vault, t_input **lst)
{
	t_input	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (tmp->type == TOKEN && tmp->next && tmp->next->is_variable)
		{
			if (!ft_strcmp(tmp->value, ">") || !ft_strcmp(tmp->value, ">>"))
				tmp->next->type = REDIRECT_OUTPUT;
			else if (!ft_strcmp(tmp->value, "<") && ft_strlen(tmp->value) == 1)
				tmp->next->type = REDIRECT_INPUT;
			else if (!ft_strcmp(tmp->value, "<< ") && ft_strlen(tmp->value) == 2)
				tmp->next->type = HEREDOC;
		}
		else if (tmp->is_variable && tmp->type == VARIABLE)
		{
			if (is_executable(vault, tmp->value) && !tmp->is_quoted)
				tmp->type = COMMAND;
			else
				tmp->type = ARGUMENT;
		}
		tmp = tmp->next;
	}
	return (1);
}
