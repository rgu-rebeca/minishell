/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauizqui <rauizqui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:59:00 by rgu               #+#    #+#             */
/*   Updated: 2025/06/21 06:56:02 by rauizqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

char	**ft_arrdup(char **arr)
{
	int		i;
	int		j;
	char	**copy;

	if (arr == NULL)
		return (NULL);
	i = 0;
	while (arr[i] != NULL)
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (copy == NULL)
		return (NULL);
	j = 0;
	while (j < i)
	{
		copy[j] = ft_strdup(arr[j]);
		if (copy[j] == NULL)
		{
			while (j-- > 0)
				free(copy[j]);
			free(copy);
			return (NULL);
		}
		j++;
	}
	copy[i] = NULL;
	return (copy);
}

void	ft_arrfree(char **arr)
{
	int	i;

	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	update_underscore(t_env **env, char *last_arg)
{
	t_env	*node;
	char	*value;

	if (last_arg == NULL)
		return ;
	value = ft_strdup(last_arg);
	if (value == NULL)
		return ;
	node = find_env_node(*env, "_");
	if (node != NULL)
	{
		free(node->value);
		node->value = value;
	}
	else
	{
		add_env_node(env, "_", value);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char *line;
	t_token *tokens;
	t_cmd *cmd;
	t_env *env_list;
	char *last_arg;

	(void)argc;
	(void)argv;
	env_list = init_env(envp);
	setup_signals();

	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line != '\0')
			add_history(line);

		tokens = tokenize(line, env_list);
		if (tokens == NULL)
		{
			free(line);
			continue ;
		}

		if (ft_strchr(line, '|') != NULL)
		{
			execute_pipeline(tokens, envp);
		}
		else
		{
			cmd = parse_tokens(tokens);
			if (is_built_in(cmd) == 1)
			{
				if (cmd->args != NULL && cmd->args[0] != NULL)
					last_arg = ft_strdup(cmd->args[0]);
				else
					last_arg = NULL;

				exec_built_in(cmd, &env_list);

				if (last_arg != NULL)
				{
					update_underscore(&env_list, last_arg);
					free(last_arg);
				}
				free_command(cmd);
			}
			else if (cmd != NULL && cmd->args != NULL && cmd->args[0] != NULL)
			{
				last_arg = ft_strdup(cmd->args[0]);
				execute_command_simple(cmd, envp);

				if (last_arg != NULL)
				{
					update_underscore(&env_list, last_arg);
					free(last_arg);
				}
				free_command(cmd);
			}
			else if (cmd != NULL)
			{
				free_command(cmd);
			}
			free_tokens(tokens);
		}
		free(line);
	}
	free_env_list(env_list);
	return (0);
}