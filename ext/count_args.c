#include "../include/minishell.h"

int	count_args(t_input *input)
{
	int count;
	t_input *tmp;

	count = 0;
	tmp = input->next;
	while (tmp && tmp->type != PIPE && tmp->type != TOKEN)
	{
		count++;
		tmp = tmp->next;
	}
	return count;
}
