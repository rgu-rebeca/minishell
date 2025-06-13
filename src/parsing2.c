/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:10:21 by rgu               #+#    #+#             */
/*   Updated: 2025/06/04 23:20:18 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*cmd;
	t_token	*current;
	int		j;

	current = tokens;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = 0;
	cmd->args = malloc(sizeof(char *) * (count_word(tokens) + 1));
	if (!cmd->args)
		return (free(cmd), NULL);
	j = 0;
	while (current)
	{
		if ((current->type == T_REDIR_OUT || current->type == T_REDIR_APPEND)
			&& current->next)
		{
			cmd->outfile = ft_strdup(current->next->value);
			cmd->append = (current->type == T_REDIR_APPEND);
			current = current->next->next;
		}
		else if (current->type == T_REDIR_IN && current->next)
		{
			cmd->infile = ft_strdup(current->next->value);
			current = current->next->next;
		}
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
