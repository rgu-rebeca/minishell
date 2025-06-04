/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:59:00 by rgu               #+#    #+#             */
/*   Updated: 2025/06/04 20:28:00 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_token	*tokens;
	t_cmd	*cmd;

	(void)argc;
	(void)argv;
	setup_signals();
	while (1)
	{
		line = readline("minishell$");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		tokens = tokenize(line);
		if (!tokens)
		{
			free(line);
			continue ;
		}
		if (ft_strchr(line, '|'))
			execute_pipeline(line, envp);
		else
		{
			cmd = parse_tokens(tokens);
			if (is_built_in(cmd) == 1)
			{
				exec_built_in(cmd);
				free_command(cmd);
			}
			else if (cmd && cmd->args && cmd->args[0])
				execute_command_simple(cmd, envp);
			free_tokens(tokens);
		}
		free(line);
	}
	return (0);
}
