/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:58:22 by rgu               #+#    #+#             */
/*   Updated: 2025/06/21 15:06:15 by rgu              ###   ########.fr       */
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
	if (cmd->heredoc_delimiter)
		free(cmd->heredoc_delimiter);
	free(cmd);
}

void	setup_redir_aux(void)
{
	perror("open error1");
	exit(1);
}

void	setup_redir(t_cmd *cmd)
{
	int	fd;
	int	flag;

	if (cmd->infile)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd < 0)
			setup_redir_aux();
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
			setup_redir_aux();
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	execute_command(t_cmd *cmd, char **envp)
{
	char	*path;

	if (!cmd || !cmd->args || !cmd->args[0])
	{
		ft_putendl_fd("minishell: invalid command", 2);
		exit(1);
	}
	setup_redir(cmd);
	path = get_command_path(cmd->args[0], envp);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	signal(SIGQUIT, SIG_DFL);
	execve(path, cmd->args, envp);
	perror("minishell error");
	free(path);
	exit(1);
}
