#include <minishell.h>

void	execute(char *path, char **flags, t_vault *vault)
{
	if(execve(path, flags, vault->envp) == -1)
	{
		perror("execve");
		exit(1);
	}
}

char	**get_flags(t_input **input, char *command)
{
	char **flags;
	char *tmp1;
	t_input *tmp;

	tmp = *input;
	while(tmp->value != command)
		tmp = tmp->next;
	tmp1 = ft_strjoin(tmp->value, " ");
	while(tmp->next && (tmp->next->type != PIPE && tmp->next->type != TOKEN))
	{
		tmp1 = ft_strjoin(tmp1, " ");
		tmp1 = ft_strjoin(tmp1, tmp->next->value);
		tmp = tmp->next;
	}
	flags = ft_split(tmp1, ' ');
	return (flags);
}

void	tmp_execute(t_input **input, t_vault *vault)
{
	t_input *tmp;
	int fd;
	int fd2;
	int flag;
	char **flags;
	char *tmp1;

	tmp =  *input;
	flag = 1;
	while(tmp)
	{
		if(tmp->type == TOKEN)
			;
		else if(tmp->type == REDIRECT_INPUT)
		{
			fd = open(tmp->value, O_RDONLY);
			dup2(fd, 0);
			close(fd);
		}
		else if(tmp->type == REDIRECT_OUTPUT)
		{
			fd2 = open(tmp->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dup2(fd2, 1);
			close(fd2);
		}
		else if(tmp->type == APPEND_OUTPUT)///////////////////
		{
			fd2 = open(tmp->value, O_WRONLY | O_CREAT | O_APPEND, 0777);
			dup2(fd2, 1);
			close(fd2);
		}
		else if(tmp->type == COMMAND && flag == 1)
		{
			flags = get_flags(input, tmp->value);
			tmp1 = flags[0];
			flag = 0;
		}
		tmp = tmp->next;
	}
	if(is_executable(tmp1))
		execute(set_path(tmp1), flags, vault);
	else
		printf("command not found\n");
	exit(1);
}
