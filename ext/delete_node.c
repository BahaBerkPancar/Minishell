#include <minishell.h>

void	delete_node(t_input **head, t_input *remove)
{
	t_input	*prev;

	if (!head || !*head || !remove)
		return ;
	if (*head == remove)
	{
		*head = remove->next;
		free(remove);
		return ;
	}
	prev = *head;
	while (prev && prev->next != remove)
		prev = prev->next;
	if (!prev)
		return ;
	prev->next = remove->next;
	free(remove);
}

void	add_after(t_input *head, t_input *new)
{
	if (!head || !new)
		return ;
	new->next = head->next;
	head->next = new;
}
