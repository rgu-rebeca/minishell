/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 20:23:08 by rgu               #+#    #+#             */
/*   Updated: 2025/06/30 23:45:43 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

extern int	g_last_status;

int	is_built_in(t_cmd *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (1);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return (1);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return (1);
	return (0);
}

void	exec_cd(t_cmd *cmd)
{
	char	*path;

	if (!cmd->args[1])
		path = getenv("HOME");
	else
		path = cmd->args[1];
	if (!path || chdir(path) != 0)
	{
		perror("cd error");
		g_last_status = 1;
	}
}

void	exec_pwd(void)
{
	char	pwd[1024];

	if (getcwd(pwd, sizeof(pwd)) == NULL)
	{
		perror("pwd error");
		g_last_status = 1;
	}
	ft_printf("%s\n", pwd);
}

int	exec_built_in(t_cmd *cmd, t_env **env_list)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		exec_echo(cmd);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		builtin_export(cmd->args, env_list);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		builtin_unset(cmd->args, env_list);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		print_env(*env_list);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		exec_cd(cmd);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		exec_pwd();
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		exec_exit(cmd);
	return (0);
}
