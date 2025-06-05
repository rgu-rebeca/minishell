/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 20:26:18 by rgu               #+#    #+#             */
/*   Updated: 2025/06/05 20:36:46 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

extern int	g_last_status;

t_token	*copy_token(t_token *src)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
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

t_token	**split_pipeline(t_token *tokens, int *count)
{
	t_token	**cmds;
	int		i;
	t_token	*start;
	t_token	*curr;

	cmds = malloc(sizeof(t_token *) * 64);
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

void	execute_pipeline(t_token *tokens, char **envp)
{
	t_token	**cmds;
	int		fd[2];
	int		in_fd;
	__pid_t	*pids;
	int		i;
	int		count;
	t_cmd	*cmd;
	int		status;

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
	i = 0;
	while (i < count)
		free_tokens(cmds[i++]);
	free_tokens(tokens);
	free(cmds);
}
