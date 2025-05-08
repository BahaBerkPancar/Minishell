#include <minishell.h>

int	clear(void)
{
	system("clear");
	return (0);
}

int	pipe_count(t_input **input)
{
	t_input *tmp;
	int count;

	tmp = *input;
	count = 0;
	while (tmp)
	{
		if (tmp->type == PIPE)
			count++;
		tmp = tmp->next;
	}
	return (count);
}
int	dollar_count(t_input **input)
{
	t_input *tmp;
	int count;

	tmp = *input;
	count = 0;
	while (tmp)
	{
		if (ft_strcmp(tmp->value, "$") == 0)
			count++;
		tmp = tmp->next;
	}
	return (count);
}