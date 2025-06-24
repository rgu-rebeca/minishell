/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:40:46 by rgu               #+#    #+#             */
/*   Updated: 2025/06/24 21:51:02 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

extern int	g_last_status;

void	handle_child(int fd[2], int in_fd, int i, int count)
{
	close(fd[0]);
	if (in_fd != STDIN_FILENO)
		dup2(in_fd, STDIN_FILENO);
	if (i < count - 1)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
}

void	handle_parent(int fd[2], int *in_fd)
{
	close(fd[1]);
	if ((*in_fd) != STDIN_FILENO)
		close(*in_fd);
	*in_fd = fd[0];
}

void	launch_pipes(int count, pid_t *pids, t_cmd **cmds, char **envp)
{
	int	in_fd;
	int	fd[2];
	int	i;

	in_fd = 0;
	i = 0;
	while (i < count)
	{
		if (pipe(fd) < 0)
			return (perror("minishell: pipe"));
		pids[i] = fork();
		if (pids[i] < 0)
			return (perror("minishell:fork"));
		if (pids[i] == 0)
		{
			handle_child(fd, in_fd, i, count);
			execute_command(cmds[i], envp);
			free_command(cmds[i]);
			exit(1);
		}
		handle_parent(fd, &in_fd);
		i++;
	}
	if (in_fd != STDIN_FILENO)
		close(in_fd);
}

static void	wait_all(int count, pid_t *pids)
{
	int	i;
	int	status;

	i = 0;
	while (i < count)
	{
		waitpid(pids[i++], &status, 0);
		if (WIFEXITED(status))
			g_last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_last_status = 128 + WTERMSIG(status);
	}
}

void	execute_pipeline(t_token *tokens, char **envp)
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
	init_cmds_pids(count, token_list, cmds);
	launch_pipes(count, pids, cmds, envp);
	wait_all(count, pids);
	unlink(".heredoc_temp");
	free(pids);
	i = 0;
	while (i < count)
		free_tokens(token_list[i++]);
	free(token_list);
	free_tokens(tokens);
	i = 0;
	while (i < count)
		free_command(cmds[i++]);
	free(cmds);
}
