#include <minishell.h>

int find_char(char *input, char c)
{
	int i;

	i = 0;
	while(input[i])
	{
		if (input[i] == c)
			break;
		i++;
	}
	return (i);
}