/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 22:42:21 by rgu               #+#    #+#             */
/*   Updated: 2025/06/21 16:01:08 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

int	is_special(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

char	*extract_especial(char *line, int *i)
{
	char	*word;

	if ((line[*i] == '>' || line[*i] == '<') && line[*i + 1] == line[*i])
	{
		word = ft_substr(line, *i, 2);
		(*i) += 2;
	}
	else
	{
		word = ft_substr(line, *i, 1);
		(*i)++;
	}
	return (word);
}

char	*extract_quoted(char *line, int *i, int *start)
{
	char	mark;
	int		len;
	char	*word;

	mark = line[(*i)++];
	*start = *i;
	while (line[*i] && line[*i] != mark)
		(*i)++;
	len = *i - *start;
	word = ft_substr((const char *)line, *start, len);
	if (line[((*i))] != mark)
		return (free(word), ft_putstr_fd("the quotation mark is not closed\n",
				2), NULL);
	else if (line[(*i)] == mark)
		(*i)++;
	return (word);
}

char	*extract_word(char *line, int *i)
{
	int		start;
	char	*word;

	word = NULL;
	while ((line[*i]) && ft_isspace(line[*i]))
		(*i)++;
	if (!line[*i])
		return (NULL);
	if (is_special(line[*i]))
	{
		word = extract_especial(line, i);
		return (word);
	}
	if (line[*i] == '\'' || line[*i] == '"')
	{
		word = extract_quoted(line, i, &start);
	}
	else
	{
		start = *i;
		while (line[*i] && !is_special(line[*i]) && !ft_isspace(line[*i]))
			(*i)++;
		word = ft_substr((const char *)line, start, *i - start);
	}
	return (word);
}

t_token_type	get_token_type(char *str)
{
	if (!str)
		return (T_WORD);
	if (ft_strcmp(str, "|") == 0)
		return (T_PIPE);
	else if (ft_strcmp(str, "<") == 0)
		return (T_REDIR_IN);
	else if (ft_strcmp(str, ">") == 0)
		return (T_REDIR_OUT);
	else if (ft_strcmp(str, ">>") == 0)
		return (T_REDIR_APPEND);
	else if (ft_strcmp(str, "<<") == 0)
		return (T_HERDOC);
	return (T_WORD);
}
