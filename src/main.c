/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:59:00 by rgu               #+#    #+#             */
/*   Updated: 2025/07/02 00:35:46 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

extern int g_last_status;

static void	handle_command(t_cmd *cmd, t_env **env_list, char **envp)
{
	char	*last_arg;

	if (!cmd)
		return ;
	if (cmd->args && cmd->args[0])
		last_arg = ft_strdup(cmd->args[0]);
	else
		last_arg = NULL;
	if (cmd->args && cmd->args[0])
		execute_command_simple(cmd, *env_list, envp);
	if (last_arg != NULL)
	{
		update_underscore(env_list, last_arg);
		free(last_arg);
	}
	free_command(cmd);
}

void	handle_builtin(t_cmd *cmd, t_env **env_list)
{
	int	copy_stdout;
	int	flags;
	int	fd;

	copy_stdout = -1;
	if (cmd->outfile)
	{
		copy_stdout = dup(STDOUT_FILENO);
		if (cmd->append)
			flags = O_APPEND;
		else
			flags = O_TRUNC;
		fd = open(cmd->outfile, O_WRONLY | O_CREAT | flags, 0644);
		if (fd < 0)
			return ((perror("open"), free_command(cmd)));
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	exec_built_in(cmd, env_list);
	if (copy_stdout != -1)
	{
		dup2(copy_stdout, STDOUT_FILENO);
		close(copy_stdout);
	}
	free_command(cmd);
}

void	handle_special_redirection(t_token *token)
{
	t_token	*head;
	int		fd;

	head = token;
	if ((head->type == T_REDIR_OUT || head->type == T_REDIR_APPEND)
		&& (access(head->next->value, F_OK) != 0))
	{
		fd = open(head->next->value, O_CREAT | O_RDONLY, 0644);
		if (fd < 0)
			return (perror("open error"), free_tokens(token));
	}
	else if (head->type == T_REDIR_IN)
	{
		if (access(head->next->value, F_OK) != 0)
			ft_printf("%s: No existe el archivo o el directorio\n",
				head->next->value);
	}
	else if (head->type == T_HERDOC)
	{
		heredoc(head->next->value, ".heredoc");
		unlink(".heredoc");
	}
	free_tokens(token);
}

static void	process_line(char *line, t_env **env_list, char **envp)
{
	t_token	*tokens;
	t_cmd	*cmd;

	cmd = NULL;
	if (!line || *line == '\0')
		return ;
	tokens = tokenize(line, *env_list);
	if (!tokens)
		return ;
	if (check_token_error(tokens) == 1)
		return (free_tokens(tokens));
	if (ft_strchr(line, '|'))
		execute_pipeline(tokens, env_list, envp);
	else if (is_redirection(tokens))
		handle_special_redirection(tokens);
	else
	{
		cmd = parse_tokens(tokens);
		if (is_built_in(cmd) == 1)
			handle_builtin(cmd, env_list);
		else
			handle_command(cmd, env_list, envp);
		free_tokens(tokens);
	}
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
		if (!line[0])
		{
			free(line);
			continue ;
		}
		add_history(line);
		process_line(line, &env_list, envp);
		free(line);
	}
	free_env_list(env_list);
	return (0);
}
