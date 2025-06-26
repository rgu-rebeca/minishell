/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 20:58:00 by rgu               #+#    #+#             */
/*   Updated: 2025/06/26 19:48:50 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

extern int	g_last_status;

static int	handle_parent_heredoc(char *filename, int pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		g_last_status = WEXITSTATUS(status);
		if (g_last_status != 0)
		{
			unlink(filename);
			return (1);
		}
	}
	else if (WIFSIGNALED(status))
	{
		g_last_status = 128 + WTERMSIG(status);
		unlink(filename);
		return (1);
	}
	return (0);
}

static int	hanlde_child_heredoc(char *filename, char *delimiter)
{
	int		fd;
	char	*line;

	signal(SIGINT, SIG_DFL);
	fd = open(filename, O_TRUNC | O_WRONLY | O_CREAT, 0600);
	if (fd < 0)
		return (perror("error opening"), 1);
	while (1)
	{
		line = readline(">");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return (0);
}

int	heredoc(char *delimiter, char *filename)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (hanlde_child_heredoc(filename, delimiter) == 1)
			exit (1);
		exit (0);
	}
	if (handle_parent_heredoc(filename, pid) == 1)
		return (1);
	return (0);
}
