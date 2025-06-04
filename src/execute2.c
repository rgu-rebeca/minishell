/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 20:26:18 by rgu               #+#    #+#             */
/*   Updated: 2025/06/04 20:27:14 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

extern int	g_last_status;

t_token	**split_pipeline(t_token *tokens, int *count)
{
	t_token	**cmds;
	int		i;
	t_token	*start;
	t_token	*curr;
	t_token	*prev;

	cmds = malloc(sizeof(t_token *) * 64);
	i = 0;
	start = tokens;
	curr = tokens;
	prev = NULL;
	while (curr)
	{
		if (curr->type == T_PIPE)
		{
			if (prev)
				prev->next = NULL;
			cmds[i++] = start;
			start = curr->next;
		}
		prev = curr;
		curr = curr->next;
	}
	if (start)
		cmds[i++] = start;
	*count = i;
	return (cmds);
}

void	execute_pipeline(char *line, char **envp)
{
	t_token	*tokens;
	t_token	**cmds;
	int		fd[2];
	int		in_fd;
	__pid_t	*pids;
	int		i;
	int		count;
	t_cmd	*cmd;
	int		status;

	tokens = tokenize(line);
	cmds = split_pipeline(tokens, &count);
	pids = malloc(sizeof(pid_t) * count);
	if (!pids)
		return ;
	in_fd = 0;
	i = 0;
	while (i < count)
	{
		if (pipe(fd) < 0)
		{
			perror("minishell: pipe");
			break ;
		}
		pids[i] = fork();
		if (pids[i] == 0)
		{
			close (fd[0]);
			if (in_fd != STDIN_FILENO)
				dup2(in_fd, STDIN_FILENO);
			if (i < count - 1)
				dup2(fd[1], STDOUT_FILENO);
			close (fd[1]);
			cmd = parse_tokens(cmds[i]);
			if (!cmd)
				exit (1);
			execute_command(cmd, envp);
			free_command(cmd);
			exit (0);
		}
		else
		{
			close(fd[1]);
			if (in_fd != STDIN_FILENO)
				close(in_fd);
			in_fd = fd[0];
		}
		i++;
	}
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	i = 0;
	while (i < count)
	{
		waitpid(pids[i++], &status, 0);
		if (WIFEXITED(status))
			g_last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_last_status = 128 + WTERMSIG(status);
	}
	free(pids);
	free_tokens(tokens);
}
