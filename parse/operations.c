#include <minishell.h>

static int find_operations(char *input, char op)
{
	int i = 0;

	while (input[i] != '\0')
	{
		if (input[i] == op)
		{
			if (input[i + 1] == op)
				return (2);
			else
				return (1);
		}
		i++;
	}
	return(0);
}

char operations_check(char *input)
{
	if (find_operations(input, '|') != 0)
	{
		if(find_operations(input, '|') == 2)
			;// printf("found ||\n");
		else
			// printf("found |\n");
		return('|');
	}
	else if (find_operations(input, '<') != 0)
	{
		if(find_operations(input, '<') == 2)
			;// printf("found <<\n");
		else
			;// printf("found <\n");
		return('<');
	}
	else if (find_operations(input, '>') != 0)
	{
		if(find_operations(input, '>') == 2)
			;// printf("found >>\n");
		else
			;// printf("found >\n");
		return('>');
	}
	else
		;// printf("no operations found\n");
	return (0);
}
