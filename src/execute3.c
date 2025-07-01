/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:40:46 by rgu               #+#    #+#             */
/*   Updated: 2025/07/02 00:04:02 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

extern int	g_last_status;

void	handle_child(int fd[2], int in_fd, int i, int count)
{
	if (fd[0] != -1)
		close(fd[0]);
	if (in_fd != STDIN_FILENO)
		dup2(in_fd, STDIN_FILENO);
	if (i < count - 1 && fd[1] != -1)
		dup2(fd[1], STDOUT_FILENO);
	if (fd[1] != -1)
		close(fd[1]);
}

void	handle_parent(int fd[2], int *in_fd)
{
	if (fd[1] != -1)
		close(fd[1]);
	if ((*in_fd) != STDIN_FILENO)
		close(*in_fd);
	if (fd[0] != -1)
		*in_fd = fd[0];
}

void	auxliar(t_cmd **cmds, char **envp, int i, t_env **env_list)
{
	if (is_built_in(cmds[i]) == 0)
		execute_command(cmds[i], envp, *env_list);
	else
		exec_built_in(cmds[i], env_list);
	free_command(cmds[i]);
	exit(1);
}
void	launch_pipes(int count, pid_t *pids, t_cmd **cmds, char **envp, t_env **env_list)
{
	int	in_fd;
	int	fd[2];
	int	i;

	in_fd = 0;
	i = 0;
	while (i < count)
	{
		fd[0] = -1;
		fd[1] = -1;
		if (i < count -1 && pipe(fd) < 0)
			return (perror("minishell: pipe"));
		pids[i] = fork();
		if (pids[i] < 0)
			return (perror("minishell:fork"));
		if (pids[i] == 0)
		{
			handle_child(fd, in_fd, i, count);
			auxliar(cmds, envp, i, env_list);
		}
		handle_parent(fd, &in_fd);
		i++;
	}
	if (in_fd != STDIN_FILENO)
		close(in_fd);
}

void	wait_all(int count, pid_t *pids)
{
	int	i;
	int	status;

	i = 0;
	while (i < count)
	{
		signal(SIGINT, handle_sigint_special);
		waitpid(pids[i++], &status, 0);
		signal(SIGINT, handle_sigint);
		if (WIFEXITED(status))
			g_last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_last_status = 128 + WTERMSIG(status);
	}
}
