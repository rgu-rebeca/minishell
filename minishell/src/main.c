/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauizqui <rauizqui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:59:00 by rgu               #+#    #+#             */
/*   Updated: 2025/06/23 20:50:27 by rauizqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

static void	handle_command(t_cmd *cmd, t_env **env_list, char **envp)
{
	char	*last_arg;

	if (!cmd)
		return ;
	if (cmd->args && cmd->args[0])
		last_arg = ft_strdup(cmd->args[0]);
	else
		last_arg = NULL;
	if (is_built_in(cmd) == 1)
		exec_built_in(cmd, env_list);
	else if (cmd->args && cmd->args[0])
		execute_command_simple(cmd, envp);
	if (last_arg != NULL)
	{
		update_underscore(env_list, last_arg);
		free(last_arg);
	}
	free_command(cmd);
}

static void	process_line(char *line, t_env **env_list, char **envp)
{
	t_token	*tokens;
	t_cmd	*cmd;

	if (!line || *line == '\0')
		return ;
	tokens = tokenize(line, *env_list);
	if (!tokens)
		return ;
	if (ft_strchr(line, '|'))
		execute_pipeline(tokens, envp);
	else
	{
		cmd = parse_tokens(tokens);
		handle_command(cmd, env_list, envp);
	}
	free_tokens(tokens);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_env	*env_list;

	(void)argc;
	(void)argv;
	env_list = init_env(envp);
	setup_signals();
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		process_line(line, &env_list, envp);
		free(line);
	}
	free_env_list(env_list);
	return (0);
}
