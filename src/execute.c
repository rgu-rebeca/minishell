/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:58:22 by rgu               #+#    #+#             */
/*   Updated: 2025/07/02 22:07:21 by rgu              ###   ########.fr       */
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
		perror("open error");
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
		perror("open error");
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	handle_redirections(t_cmd *cmd)
{
	open_infile(cmd);
	open_outfile(cmd);
}

void	print_path_error(t_cmd *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->args[0], 2);
	ft_putendl_fd(": command not found", 2);
	free_command(cmd);
	exit(127);
}

void	execute_command(t_cmd *cmd, t_exec_data *data)
{
	char	*path;

	if (!cmd || !cmd->args || !cmd->args[0])
	{
		ft_putendl_fd("minishell: invalid command", 2);
		exit(1);
	}
	handle_redirections(cmd);
	if (access(".heredoc_temp", F_OK) == 0)
		unlink(".heredoc_temp");
	path = get_command_path(cmd->args[0], data->env_list);
	if (!path)
		print_path_error(cmd);
	signal(SIGQUIT, SIG_DFL);
	if (data-> dirty_envp)
		data->envp = update_envp(data);
	execve(path, cmd->args, data->envp);
	perror("minishell error");
	free(path);
	exit(1);
}
