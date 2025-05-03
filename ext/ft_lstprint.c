#include <minishell.h>

void ft_lstprint(t_input *lst)
{
	while (lst != NULL)
	{
		printf("(%s)->", lst->value);
		// printf("Type: %d\n", lst->type);
		// printf("is_doublequoted = %d\n", lst->is_doublequoted);
		lst = lst->next;
	}
	printf("NULL\n");
}