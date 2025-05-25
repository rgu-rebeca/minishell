/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:58:22 by rgu               #+#    #+#             */
/*   Updated: 2025/05/25 16:34:59 by rgu              ###   ########.fr       */
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

	if (!cmd || !cmd->args || !cmd->args[0])
{
	ft_putendl_fd("minishell: invalid command", 2);
	exit(1);
}

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
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
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
	{
		execute_command(cmd, envp);
		exit (1);
	}
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
		//printf("parsing token: %s, type: %d\n", current->value, current->type);

		if ((current->type == T_REDIR_OUT || current->type == T_REDIR_APPEND) && current->next)
		{
			cmd->outfile = ft_strdup(current->next->value);
			cmd->append = (current->type == T_REDIR_APPEND);
			current = current->next->next;
		}
		else if (current->type == T_REDIR_IN && current->next)
		{
			cmd->infile = ft_strdup(current->next->value);
			current = current->next->next;
		}
		else if (current->type == T_WORD)
		{
			cmd->args[j++] = ft_strdup(current->value);
			current = current->next;
		}
		else
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
	__pid_t	*pids;
	int		i;
	int		count;
	t_cmd	*cmd;

	tokens = tokenize(line);
	cmds = split_pipeline(tokens, &count);
	pids = malloc(sizeof(pid_t) * count);
	if (!pids)
		return ;
	in_fd = 0;
	i = 0;
	while (i < count)
	{
		if (pipe(fd) < 0)
		{
			perror("minishell: pipe");
			break; // or return
		}

		pids[i] = fork();
		if (pids[i] == 0)
		{
			close (fd[0]);
			if (in_fd != STDIN_FILENO)
				dup2(in_fd, STDIN_FILENO);
			if (i < count - 1)
				dup2(fd[1], STDOUT_FILENO);
			close (fd[1]);
			cmd = parse_tokens(cmds[i]);
			if (!cmd)
				exit (1);
			execute_command(cmd, envp);
			free_command(cmd);
			exit (0);
		}
		else
		{
			close(fd[1]);
			if (in_fd != STDIN_FILENO)
				close(in_fd);
			in_fd = fd[0];
		}
		i++;
	}
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	i = 0;
	while (i < count)
		waitpid(pids[i++], NULL, 0);
	free(pids);
	free_tokens(tokens);
}