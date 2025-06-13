/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:58:22 by rgu               #+#    #+#             */
/*   Updated: 2025/06/04 20:26:33 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

int		g_last_status = 0;

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
}

void	free_command(t_cmd *cmd)
{
	if (!cmd)
		return ;
	free_args(cmd->args);
	if (cmd->infile)
		free(cmd->infile);
	if (cmd->outfile)
		free(cmd->outfile);
	free(cmd);
}

void	execute_command(t_cmd *cmd, char **envp)
{
	char	*path;
	int		fd;
	int		flag;

	if (!cmd || !cmd->args || !cmd->args[0])
	{
		ft_putendl_fd("minishell: invalid command", 2);
		exit(1);
	}
	if (cmd->infile)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd < 0)
		{
			perror("open error1");
			exit(1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (cmd->outfile)
	{
		flag = O_WRONLY | O_CREAT;
		if (cmd->append == 1)
			flag |= O_APPEND;
		else
			flag |= O_TRUNC;
		fd = open(cmd->outfile, flag, 0644);
		if (fd < 0)
		{
			perror("open error2");
			exit(1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	path = get_command_path(cmd->args[0], envp);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	execve(path, cmd->args, envp);
	perror("minishell error");
	free(path);
	exit(1);
}

void	execute_command_simple(t_cmd *cmd, char **envp)
{
	__pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		execute_command(cmd, envp);
		exit(1);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_last_status = 128 + WTERMSIG(status);
	}
	else
		perror("fork");
	free_command(cmd);
}
