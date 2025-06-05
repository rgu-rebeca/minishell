/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 20:23:08 by rgu               #+#    #+#             */
/*   Updated: 2025/06/05 20:37:25 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

int	is_built_in(t_cmd *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (1);
	return (0);
}

void	exec_built_in(t_cmd *cmd)
{
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		exec_cd(cmd);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		exec_pwd();
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		exec_exit(cmd);
}

void	exec_cd(t_cmd *cmd)
{
	char	*path;

	if (!cmd->args[1])
		path = getenv("HOME");
	else
		path = cmd->args[1];
	if (!path || chdir(path) != 0)
		perror("cd error");
}

void	exec_pwd(void)
{
	char	pwd[1024];

	if (getcwd(pwd, sizeof(pwd)) == NULL)
		perror("pwd error");
	ft_printf("%s\n", pwd);
}
