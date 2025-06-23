/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauizqui <rauizqui@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:46:26 by rauizqui          #+#    #+#             */
/*   Updated: 2025/06/23 19:48:03 by rauizqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

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
	if (cmd->args_owner)
	{
		printf("[FREE] args\n");
		free_args(cmd->args);
	}
	if (cmd->infile)
	{
		printf("[FREE] infile -> %s\n", cmd->infile);
		free(cmd->infile);
	}
	if (cmd->outfile)
	{
		printf("[FREE] outfile -> %s\n", cmd->outfile);
		free(cmd->outfile);
	}
	if (cmd->heredoc_delimiter)
	{
		printf("[FREE] heredoc_delimiter -> %s\n", cmd->heredoc_delimiter);
		free(cmd->heredoc_delimiter);
	}
	printf("[FREE] cmd struct\n");
	free(cmd);
}
