/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:16:02 by rgu               #+#    #+#             */
/*   Updated: 2025/06/24 20:21:42 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

extern int	g_last_status;

int	is_redirection(t_token *token)
{
	return (token->type == T_HERDOC || token->type == T_REDIR_APPEND
		|| token->type == T_REDIR_IN || token->type == T_REDIR_OUT);
}

int	is_special_token(t_token *token)
{
	return (token->type == T_HERDOC || token->type == T_PIPE
		|| token->type == T_REDIR_IN || token->type == T_REDIR_OUT
		|| token->type == T_REDIR_APPEND);
}

void	syntax_error(t_token *token)
{
	ft_printf("syntax error near unexpected element: %s\n", token->value);
	g_last_status = 2;
}

int	check_token_error(t_token *token)
{
	t_token	*curr;

	if (!token)
		return (0);
	curr = token;
	if (curr->type == T_PIPE)
		return (syntax_error(curr), 1);
	while (curr)
	{
		if (curr->type == T_PIPE && !curr->next)
			return (syntax_error(curr), 1);
		if (curr->type == T_PIPE && curr->next->type == T_PIPE)
			return (syntax_error(curr), 1);
		if (is_redirection(curr) == 1)
		{
			if (!curr->next)
				return (syntax_error(curr), 1);
			if (is_special_token(curr->next))
				return (syntax_error(curr), 1);
		}
		curr = curr->next;
	}
	if (curr && curr->type == T_PIPE)
		return (syntax_error(curr), 1);
	return (0);
}
