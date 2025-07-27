#include "../include/minishell.h"


void	ft_lstprint(t_input *lst)
{
	t_input	*tmp;

	tmp = lst;
	while (tmp != NULL)
	{
		printf("(%s)->", tmp->value);
		tmp = tmp->next;
	}
	printf("NULL\n");
	while (lst != NULL)
	{
		printf("(%u)->", lst->type);
		lst = lst->next;
	}
	printf("NULL\n");
}
