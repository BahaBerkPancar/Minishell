#include "../include/minishell.h"


t_input	*lstlast(t_input *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	last_node(t_input **lst, t_input *new)
{
	t_input	*temp;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	temp = lstlast(*lst);
	temp->next = new;
}
