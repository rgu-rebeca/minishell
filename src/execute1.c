/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauizqui <rauizqui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 15:05:30 by rgu               #+#    #+#             */
/*   Updated: 2025/06/23 20:34:28 by rauizqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

extern int	g_last_status;

void	wait_pid(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		g_last_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGQUIT)
			ft_printf("\n");
	}
}

void	handle_heredoc(t_cmd *cmd)
{
	if (cmd->heredoc_flag)
	{
		heredoc(cmd->heredoc_delimiter, ".heredoc_temp");
		if (cmd->infile)
			free(cmd->infile);
		cmd->infile = ft_strdup(".heredoc_temp");
	}
}

void	execute_command_simple(t_cmd *cmd, char **envp)
{
	__pid_t	pid;
	int		status;

	handle_heredoc(cmd);
	pid = fork();
	if (pid == 0)
	{
		execute_command(cmd, envp);
		exit(1);
	}
	else if (pid < 0)
		perror("fork");
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_last_status = 128 + WTERMSIG(status);
	}
}
