/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauizqui <rauizqui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:59:00 by rgu               #+#    #+#             */
/*   Updated: 2025/06/09 20:14:08 by rauizqui         ###   ########.fr       */
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
		{
			break ;
		}
		if (*line)
			add_history(line);

		// if (ft_strncmp(line, "testsigterm", 11) == 0)
		// {
		// 	run_child();
		// 	free(line);
		// 	continue;
		// }
		// if (ft_strncmp(line, "testsigchld", 11) == 0)
		// {
		// 	pid_t pid = fork();
		// 	if (pid == 0)
		// 	{
		// 		// Código del hijo
		// 		write(1, "Hijo dice hola y termina\n", 28);
		// 		exit(42); // El hijo termina con código 42
		// 	}
		// 	else if (pid > 0)
		// 	{
		// 		write(1, "Padre no espera, SIGCHLD lo gestiona\n", 42);
		// 	}
		// 	continue;
		// }

		tokens = tokenize(line);
		if (!tokens)
		{
			free(line);
			continue ;
		}
		if (ft_strchr(line, '|'))
		{
			execute_pipeline(tokens, envp);
		}
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
