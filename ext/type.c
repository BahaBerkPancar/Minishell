// #include "../minishell.h"

// static void set_types_helper(t_input *lst)
// {
// 	while(lst)
// 	{
// 		if (lst->next->type == REDIRECT_OUTPUT)
// 		{
// 			lst->next->next->type_info->type = "output";
// 			lst->type_info->fd[0] = 0;
// 			lst->type_info->fd[1] = 2;
// 		}
// 		else if (lst->next->type == APPEND_OUTPUT)
// 		{
// 			lst->next->next->type_info->type = "append output";
// 			lst->type_info->fd[0] = 0;/////////////
// 			lst->type_info->fd[1] = 2;
// 		}
// 		else if (lst->next->type == REDIRECT_INPUT)
// 		{
// 			lst->next->next->type_info->type = "input";
// 			lst->type_info->fd[0] = 2;
// 			lst->type_info->fd[1] = 1;
// 		}
// 		else if (lst->next->type == HEREDOC)
// 		{
// 			lst->next->next->type_info->type = "heredoc";
// 			lst->next->next->type_info->fd[0] = 0;////////////////////////////
// 			lst->next->next->type_info->fd[1] = 2;
// 		}
// 		else
// 		{
// 			lst->next->next->type_info->type = "command";
// 			lst->next->next->type_info->fd[0] = 0;
// 			lst->next->next->type_info->fd[1] = 1;
// 		}
// 		lst = lst->next;
// 	}
// }

// void set_types(t_input *lst)
// {
// 	while (lst != NULL)
// 	{
// 		if (lst->value[0] == '|')
// 			lst->type = PIPE;
// 		else if (lst->value[0] == '>')
// 			lst->type = REDIRECT_OUTPUT;
// 		else if (lst->value[0] == '<')
// 			lst->type = REDIRECT_INPUT;
//  	 	else
// 			lst->type = COMMAND;
// 		lst = lst->next;
// 	}
// 	set_types_helper(lst);
// }