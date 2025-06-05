/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 22:42:21 by rgu               #+#    #+#             */
/*   Updated: 2025/06/05 20:36:27 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

int	is_special(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

char	*extract_word(char *line, int *i)
{
	char	mark;
	int		start;
	char	*word;
	int		len;

	mark = 0;
	while ((line[*i]) && ft_isspace(line[*i]))
		(*i)++;
	if (!line[*i])
		return (NULL);
	if (is_special(line[*i]))
	{
		if ((line[*i] == '>' || line[*i] == '<')
			&& line[*i + 1] == line[*i])
		{
			word = ft_substr(line, *i, 2);
			*i += 2;
		}
		else
		{
			word = ft_substr(line, *i, 1);
			(*i)++;
		}
		return (word);
	}
	if (line[*i] == '\'' || line[*i] == '"')
	{
		mark = line[(*i)++];
		start = *i;
		while (line[*i] && line[*i] != mark)
			(*i)++;
		len = *i - start;
		word = ft_substr((const char *)line, start, len);
		if (line[((*i))] != mark)
			return (free(word),
				ft_putstr_fd("the quotation mark is not closed\n", 2), NULL);
		else if (line[(*i)] == mark)
			(*i)++;
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

void	free_tokens(t_token *tokens)
{
	t_token	*temp;

	while (tokens)
	{
		temp = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = temp;
	}
}

t_token	*tokenize(char *line)
{
	int		i;
	char	*word;
	char	*temp;
	t_token	*new_token;
	t_token	*head;
	t_token	*last;

	i = 0;
	head = NULL;
	last = NULL;
	while (line[i])
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (!line[i])
			break ;
		word = extract_word(line, &i);
		if (!word)
		{
			free_tokens(head);
			return (NULL);
		}
		temp = word;
		word = expand_env_vars(word);
		if (temp != word)
			free(temp);
		if (!word)
			return (free(temp), free_tokens(head), NULL);
		new_token = malloc(sizeof(t_token));
		if (!new_token)
			return (free(word), free_tokens(head), NULL);
		new_token->type = get_token_type(word);
		new_token->value = word;
		new_token->next = NULL;
		if (!head)
			head = new_token;
		else
			last->next = new_token;
		last = new_token;
	}
	return (head);
}
