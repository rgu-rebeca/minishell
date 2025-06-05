/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 20:23:27 by rgu               #+#    #+#             */
/*   Updated: 2025/06/05 20:37:49 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

extern int	g_last_status;

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i])
	{
		if ('0' < str[i] && str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	exec_exit(t_cmd *cmd)
{
	int	i;
	int	code;

	i = 0;
	while (cmd->args[i])
		i++;
	if (i == 0)
		exit(g_last_status);
	if (!is_numeric(cmd->args[i]))
		exit(255);
	if (i > 1)
	{
		ft_putstr_fd("exit:too many arguments\n", 2);
		exit(1);
	}
	code = ft_atoi(cmd->args[1]);
	exit(code);
}
