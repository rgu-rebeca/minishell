/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:58:22 by rgu               #+#    #+#             */
/*   Updated: 2025/05/25 14:53:20 by rgu              ###   ########.fr       */
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
	free_args(cmd->args);
	if (cmd->infile)
		free(cmd->infile);
	if (cmd->outfile)
		free(cmd->outfile);
	free(cmd);
}

void	execute_command (t_cmd *cmd, char **envp)
{
	char	*path;
	int		fd;
	int		flag;

	if (cmd->infile)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd < 0)
		{
			perror("open error1");
			exit (1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (cmd->outfile)
	{
		flag = O_WRONLY | O_CREAT;
		if (cmd->append == 1)
			flag |= O_APPEND;
		else
			flag |= O_TRUNC;
		fd = open(cmd->outfile, flag, 0644);
		if (fd < 0)
		{
			perror("open error2");
			exit (1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	path = get_command_path(cmd->args[0], envp);
	if (!path)
	{
		ft_printf("minishell: %s, command not found\n", cmd->args[0]);
		exit (1);
	}
	execve(path, cmd->args, envp);
	perror("minishell error");
	free(path);
	exit (1);
}

void	execute_command_simple(t_cmd *cmd, char **envp)
{
	__pid_t	pid;

	pid = fork();
	if (pid == 0)
		execute_command(cmd, envp);
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	else
		perror("fork");
	free_command(cmd);
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*cmd;
	t_token	*current;
	int		j;

	current = tokens;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = 0;
	cmd->args = malloc(sizeof(char *) * (count_word(tokens) + 1));
	if (!cmd->args)
		return (free(cmd), NULL);
	j = 0;
	while (current)
	{
		if ((current->type == T_REDIR_OUT || current->type == T_REDIR_APPEND) && current->next)
		{
			cmd->outfile = ft_strdup(current->next->value);
			cmd->append = (current->type == T_REDIR_APPEND);
			current = current->next;
		}
		else if (current->type == T_REDIR_IN && current->next)
		{
			cmd->infile = ft_strdup(current->next->value);
			current = current->next;
		}
		else if (current->type == T_WORD)
			cmd->args[j++] = ft_strdup(current->value);
		current = current->next;
	}
	cmd->args[j] = NULL;
	return (cmd);
}

t_token	**split_pipeline(t_token *tokens, int *count)
{
	t_token	**cmds;
	int		i;
	t_token	*start;
	t_token	*curr;
	t_token	*prev;

	cmds = malloc(sizeof(t_token *) * 64);
	i = 0;
	start = tokens;
	curr = tokens;
	prev = NULL;
	while (curr)
	{
		if (curr->type == T_PIPE)
		{
			if (prev)
				prev->next = NULL;
			cmds[i++] = start;
			start = curr->next;
		}
		prev = curr;
		curr = curr->next;
	}
	if (start)
		cmds[i++] = start;
	*count = i;
	return (cmds);
}

void	execute_pipeline(char *line, char **envp)
{
	t_token	*tokens;
	t_token	**cmds;
	int		fd[2];
	int		in_fd;
	__pid_t	pid;
	int		i;
	int		count;
	t_cmd	*cmd;

	tokens = tokenize(line);
	cmds = split_pipeline(tokens, &count);
	in_fd = 0;
	i = 0;
	while (i < count)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			close (fd[0]);
			dup2(in_fd, STDIN_FILENO);
			if (i < count - 1)
				dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			cmd = parse_tokens(cmds[i]);
			if (!cmd)
				exit (1);
			execute_command(cmd, envp);
			free_command(cmd);
			exit (0);
		}
		else
		{
			waitpid(pid, NULL, 0);
			close(fd[1]);
			if (in_fd != STDIN_FILENO)
				close(in_fd);
			in_fd = fd[0];
			i++;
		}
	}
	free_tokens(tokens);
}