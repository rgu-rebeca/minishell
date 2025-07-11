/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 22:42:21 by rgu               #+#    #+#             */
/*   Updated: 2025/07/11 10:54:32 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

extern int	g_last_status;

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
		return (g_last_status = 1, free(word),
			ft_putstr_fd("the quotation mark is not closed\n",
				2), NULL);
	else if (line[(*i)] == mark)
		(*i)++;
	return (word);
}

static char	*extract_unquoted_word(char *line, int *i)
{
	int		start;
	char	*word;
	char	mark;

	start = *i;
	while (line[*i] && !is_special(line[*i]) && !ft_isspace(line[*i]))
	{
		if (line[*i] == '=' && (line[*i + 1] == '"' || line[*i + 1] == '\''))
		{
			mark = line[*i + 1];
			*i += 2;
			while (line[*i] && line[*i] != mark)
				(*i)++;
			if (line[*i] == mark)
				(*i)++;
			else
				return (g_last_status = 1,
					printf("quotation mark not closed.\n"), NULL);
			break ;
		}
		(*i)++;
	}
	word = ft_substr(line, start, *i - start);
	return (word);
}

char	*extract_word(char *line, int *i, int *quote_type)
{
	int	start;

	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
	if (!line[*i])
		return (NULL);
	if (line[*i] == '\'')
	{
		*quote_type = 1;
		return (extract_quoted(line, i, &start));
	}
	if (line[*i] == '"')
	{
		*quote_type = 2;
		return (extract_quoted(line, i, &start));
	}
	if (is_special(line[*i]) && *quote_type == 0)
		return (extract_especial(line, i));
	*quote_type = 0;
	return (extract_unquoted_word(line, i));
}
