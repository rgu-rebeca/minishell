/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:10:21 by rgu               #+#    #+#             */
/*   Updated: 2025/06/24 23:40:05 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

extern int	g_last_status;

t_cmd	*init_cmd(t_token *tokens)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = 0;
	cmd->args = malloc(sizeof(char *) * (count_word(tokens) + 1));
	if (!cmd->args)
		return (free(cmd), NULL);
	cmd->heredoc_delimiter = NULL;
	cmd->heredoc_flag = 0;
	return (cmd);
}

int	handle_redir_logic(t_cmd **cmd, t_token **current, t_token_type type)
{
	char	*tmp;

	tmp = ft_strdup((*current)->next->value);
	if (!tmp)
		return (-1);
	if (type == T_REDIR_OUT || type == T_REDIR_APPEND)
	{
		free((*cmd)->outfile);
		(*cmd)->outfile = tmp;
		(*cmd)->append = (type == T_REDIR_APPEND);
	}
	else if (type == T_REDIR_IN)
	{
		free((*cmd)->infile);
		(*cmd)->infile = tmp;
	}
	else if (type == T_HERDOC)
	{
		free((*cmd)->heredoc_delimiter);
		(*cmd)->heredoc_delimiter = tmp;
		(*cmd)->heredoc_flag = 1;
	}
	*current = (*current)->next->next;
	return (0);
}

int	handle_redirection(t_cmd **cmd, t_token **current)
{
	t_token_type	type;

	if (!(*current) || !(*current)->next)
		return (-1);
	type = (*current)->type;
	if (type == T_REDIR_OUT || type == T_REDIR_APPEND || type == T_REDIR_IN
		|| type == T_HERDOC)
		return (handle_redir_logic(cmd, current, type));
	return (-1);
}

static int	process_token(t_cmd **cmd, t_token **cur, int *j)
{
	t_token_type	type;

	if (!cur || !(*cur))
		return (-1);
	type = (*cur)->type;
	if (type == T_REDIR_OUT || type == T_REDIR_APPEND || type == T_REDIR_IN
		|| type == T_HERDOC)
	{
		if (handle_redirection(cmd, cur) == -1)
			return (-1);
	}
	else if (type == T_WORD)
	{
		(*cmd)->args[*j] = ft_strdup((*cur)->value);
		if (!(*cmd)->args[*j])
			return (-1);
		(*j)++;
		*cur = (*cur)->next;
	}
	else
		*cur = (*cur)->next;
	return (0);
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*cmd;
	t_token	*cur;
	int		j;

	cmd = init_cmd(tokens);
	if (!cmd)
		return (NULL);
	cur = tokens;
	if (!cur)
	{
		free_command(cmd);
		return (NULL);
	}
	j = 0;
	while (cur)
	{
		if (process_token(&cmd, &cur, &j) == -1)
		{
			free_command(cmd);
			return (NULL);
		}
	}
	cmd->args[j] = NULL;
	return (cmd);
}
