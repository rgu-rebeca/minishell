/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauizqui <rauizqui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:58:36 by rgu               #+#    #+#             */
/*   Updated: 2025/06/09 20:35:36 by rauizqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_sigterm(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	exit(0);
}
void	handle_sigchld(int sig)
{
	int		status;
	pid_t	pid;

	(void)sig;
	while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
	{
		if (WIFEXITED(status))
			printf("Child process %d terminated with code:%d", pid,
				WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			printf("Child process %d terminates by signal %d", pid,
				WTERMSIG(status));
	}
}

void	handle_sigtstp(int sig)
{
	(void)sig;
	write(1, "Recibido SIGTSTP e ignorado", 28);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

void	handle_sigwinch(int sig)
{
	struct winsize	win;

	(void)sig;
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &win) == -1)
		return ;
	printf("\n Terminal resized: %d columns, %d rows\n", win.ws_col,
		win.ws_row);
	rl_resize_terminal();
	rl_on_new_line();
	rl_redisplay();
}
void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, handle_sigterm);
	signal(SIGCHLD, handle_sigchld);
	signal(SIGTSTP, handle_sigtstp);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGWINCH, handle_sigwinch);
}