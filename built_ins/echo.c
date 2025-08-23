#include "../include/minishell.h"

void echo(char **arg)
{
	int i;

	i = 1;
	if (arg[1] == NULL)
	{
		printf("\n");
		return ;
	}
	if (ft_strcmp(arg[1], "-n") == 0)
		i++;
	while (arg[i])
	{
		printf("%s", arg[i]);
		if (arg[i + 1])
			printf(" ");
		i++;
	}
	if (arg[1] == NULL || ft_strcmp(arg[1], "-n") != 0)
		printf("\n");
}
