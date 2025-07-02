/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 20:26:18 by rgu               #+#    #+#             */
/*   Updated: 2025/07/02 20:27:47 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

extern int	g_last_status;

t_token	*copy_token(t_token *src)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = src->type;
	new->value = ft_strdup(src->value);
	if (!new->value)
		return (free(new), NULL);
	new->next = NULL;
	return (new);
}

t_token	*copy_list(t_token *start, t_token *end)
{
	t_token	*head;
	t_token	*last;
	t_token	*node;

	head = NULL;
	last = NULL;
	while (start && start != end)
	{
		node = copy_token(start);
		if (!node)
			return (free_tokens(head), NULL);
		if (!head)
			head = node;
		else
			last->next = node;
		last = node;
		start = start->next;
	}
	return (head);
}

int	count_cmds(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		if (tokens->type == T_PIPE)
			i++;
		tokens = tokens->next;
	}
	return (i + 1);
}

t_token	**split_pipeline(t_token *tokens, int *count)
{
	t_token	**cmds;
	int		i;
	t_token	*start;
	t_token	*curr;
	int		cmds_count;

	cmds_count = count_cmds(tokens);
	cmds = malloc(sizeof(t_token *) * cmds_count);
	i = 0;
	start = tokens;
	curr = tokens;
	while (curr)
	{
		if (curr->type == T_PIPE)
		{
			cmds[i++] = copy_list(start, curr);
			start = curr->next;
		}
		curr = curr->next;
	}
	if (start)
		cmds[i++] = copy_list(start, NULL);
	*count = i;
	return (cmds);
}

int	init_cmds_pids(int count, t_token **token_list, t_cmd **cmds)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (i < count)
	{
		cmds[i] = parse_tokens(token_list[i]);
		if (!cmds[i])
			return (1);
		if (cmds[i]->heredoc_flag == 1)
		{
			a = heredoc(cmds[i]->heredoc_delimiter, ".heredoc_temp");
			if (cmds[i]->infile)
				free(cmds[i]->infile);
			if (a == 0)
			{
				cmds[i]->infile = ft_strdup(".heredoc_temp");
			}
			else if (a == 1)
				return (1);
		}
		i++;
	}
	return (0);
}
