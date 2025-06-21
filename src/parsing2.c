/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:10:21 by rgu               #+#    #+#             */
/*   Updated: 2025/06/21 16:37:14 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

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

void	handle_redirection(t_cmd **cmd, t_token **current)
{
	if (((*current)->type == T_REDIR_OUT || (*current)->type == T_REDIR_APPEND)
		&& (*current)->next)
	{
		(*cmd)->outfile = ft_strdup((*current)->next->value);
		(*cmd)->append = ((*current)->type == T_REDIR_APPEND);
		*current = (*current)->next->next;
	}
	else if ((*current)->type == T_REDIR_IN && (*current)->next)
	{
		(*cmd)->infile = ft_strdup((*current)->next->value);
		*current = (*current)->next->next;
	}
	else if ((*current)->type == T_HERDOC && (*current)->next)
	{
		(*cmd)->heredoc_delimiter = ft_strdup((*current)->next->value);
		(*cmd)->heredoc_flag = 1;
		*current = (*current)->next->next;
	}
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*cmd;
	t_token	*current;
	int		j;

	current = tokens;
	cmd = init_cmd(tokens);
	j = 0;
	while (current)
	{
		if (current->type == T_REDIR_OUT || current->type == T_REDIR_APPEND
			|| current->type == T_REDIR_IN || current->type == T_HERDOC)
			handle_redirection(&cmd, &current);
		else if (current->type == T_WORD)
		{
			cmd->args[j++] = ft_strdup(current->value);
			current = current->next;
		}
		else
			current = current->next;
	}
	cmd->args[j] = NULL;
	return (cmd);
}
