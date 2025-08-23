/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubleqoute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpancar <bpancar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:56:57 by skalkan           #+#    #+#             */
/*   Updated: 2025/08/24 02:47:06 by bpancar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*remove_double_quotes(char *str, int i)
{
	char	*final;
	char	*remaining;
	char	*temp;
	char	*joined;

	final = ft_strdup("");
	remaining = str;
	while (*remaining)
	{
		i = 0;
		while (remaining[i] != '\"' && remaining[i])
			i++;
		temp = ft_substr(remaining, 0, i);
		joined = ft_strjoin(final, temp);
		free(temp);
		free(final);
		final = joined;
		if (remaining[i])
			i++;
		temp = remaining;
		remaining = ft_strdup(remaining + i);
		free(temp);
	}
	free(remaining);
	return (final);
}

t_input	*get_rid_of_dquotes(t_input **list)
{
	t_input	*tmp;
	char	*new_value;

	tmp = *list;
	while (tmp)
	{
		if (ft_strchr(tmp->value, '\"')
			&& tmp->is_doublequoted && !tmp->is_quoted)
		{
			new_value = remove_double_quotes(tmp->value, 0);
			tmp->value = ft_strdup(new_value);
			free(new_value);
		}
		tmp = tmp->next;
	}
	return (*list);
}

char	*seperate_dquotes(t_input **list, char *input, char *quoted)
{
	size_t	qlen;
	size_t	ilen;

	qlen = ft_strlen(quoted);
	ilen = ft_strlen(input);
	if (!quoted || qlen == 0)
	{
		last_node(list, new_node(ft_strdup("\"\"")));
		return (input + 2);
	}
	last_node(list, new_node(ft_strdup(quoted)));
	if (lstlast(*list))
		lstlast(*list)->is_doublequoted = true;
	if (ft_strncmp(input, quoted, qlen) == 0)
	{
		if (ilen > qlen + 1)
			return (input + qlen + 1);
		else
			return (input + ilen);
	}
	return (input);
}

int	find_dquote_location(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\"')
			return (i);
		i++;
	}
	return (0);
}

char	*doublequote_check(char *temp)
{
	int		i;
	int		j;
	char	*tmp;
	char	*old_tmp;

	while (dquote_count(temp) > 2)
	{
		old_tmp = temp;
		temp = ft_substr(old_tmp, 0, ft_strlen(old_tmp) - 1);
		free(old_tmp);
	}
	i = find_dquote_location(temp);
	j = find_dquote_location(temp + i + 1) + i + 1;
	tmp = ft_substr(temp, j, ft_strlen(temp) - j);
	while (ft_strchr(tmp, ' '))
	{
		free(tmp);
		old_tmp = temp;
		temp = ft_substr(old_tmp, 0, ft_strlen(old_tmp) - 1);
		free(old_tmp);
		tmp = ft_substr(temp, j, ft_strlen(temp) - j);
	}
	if (!temp || !*temp)
		return (free(tmp), free(temp), ft_strdup(""));
	return (free(tmp), temp);
}
