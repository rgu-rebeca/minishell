/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:53:18 by rgu               #+#    #+#             */
/*   Updated: 2025/07/02 15:02:30 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

void	free_token_list(int count, t_token **token_list)
{
	int	i;

	i = 0;
	while (i < count)
		free_tokens(token_list[i++]);
	free(token_list);
}

void	free_2(t_cmd **cmds, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (cmds[i])
			free_command(cmds[i]);
		i++;
	}
	free(cmds);
}

static void	clean_and_free(pid_t *pids, int count,
			t_token **token_list, t_token *tokens)
{
	if (access(".heredoc_temp", F_OK) == 0)
		unlink(".heredoc_temp");
	free(pids);
	free_token_list(count, token_list);
	free_tokens(tokens);
}

void	execute_pipeline(t_token *tokens, t_exec_data *data)
{
	t_token	**token_list;
	__pid_t	*pids;
	int		i;
	int		count;
	t_cmd	**cmds;

	token_list = split_pipeline(tokens, &count);
	cmds = malloc(sizeof(t_cmd *) * count);
	pids = malloc(sizeof(pid_t) * count);
	if (!pids || !cmds)
		return ;
	i = 0;
	while (i < count)
		cmds[i++] = NULL;
	if (init_cmds_pids(count, token_list, cmds) == 1)
		return (free_tokens(tokens),
			free(pids), free_token_list(count, token_list),
			free_2(cmds, count));
	launch_pipes(count, pids, cmds, data);
	wait_all(count, pids);
	clean_and_free(pids, count, token_list, tokens);
	free_2(cmds, count);
}
