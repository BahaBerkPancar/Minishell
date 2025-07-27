#include "../include/minishell.h"


t_input	*lstlast(t_input *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}