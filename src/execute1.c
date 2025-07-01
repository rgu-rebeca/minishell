/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 15:05:30 by rgu               #+#    #+#             */
/*   Updated: 2025/07/02 00:28:41 by rgu              ###   ########.fr       */
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

int	handle_heredoc(t_cmd *cmd)
{
	int	a;

	a = 0;
	if (cmd->heredoc_flag)
	{
		a = heredoc(cmd->heredoc_delimiter, ".heredoc_temp");
		if (cmd->infile)
			free(cmd->infile);
		if (a == 0)
			cmd->infile = ft_strdup(".heredoc_temp");
		else if (a == 1)
			return (1);
	}
	return (0);
}

void	execute_command_simple(t_cmd *cmd, t_env *env_list, char **envp)
{
	__pid_t	pid;
	int		status;

	if (handle_heredoc(cmd) == 1)
		return ;
	pid = fork();
	if (pid == 0)
	{
		execute_command(cmd, env_list, envp);
		exit(1);
	}
	else if (pid < 0)
		perror("fork");
	else
	{
		signal(SIGINT, handle_sigint_special);
		waitpid(pid, &status, 0);
		signal(SIGINT, handle_sigint);
		if (WIFEXITED(status))
			g_last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_last_status = 128 + WTERMSIG(status);
	}
}
