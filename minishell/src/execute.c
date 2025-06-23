/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauizqui <rauizqui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:58:22 by rgu               #+#    #+#             */
/*   Updated: 2025/06/23 19:47:48 by rauizqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

int			g_last_status = 0;

static void	open_infile(t_cmd *cmd)
{
	int	fd;

	if (!cmd->infile)
		return ;
	fd = open(cmd->infile, O_RDONLY);
	if (fd < 0)
	{
		perror("open error1");
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	open_outfile(t_cmd *cmd)
{
	int	fd;
	int	flag;

	if (!cmd->outfile)
		return ;
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

static void	handle_redirections(t_cmd *cmd)
{
	open_infile(cmd);
	open_outfile(cmd);
}

void	execute_command(t_cmd *cmd, char **envp)
{
	char	*path;

	if (!cmd || !cmd->args || !cmd->args[0])
	{
		ft_putendl_fd("minishell: invalid command", 2);
		exit(1);
	}
	handle_redirections(cmd);
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
