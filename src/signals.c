/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:58:36 by rgu               #+#    #+#             */
/*   Updated: 2025/06/26 20:02:25 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_sigint_special(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void	handle_sigterm(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	ft_printf("Terminado por SIGTERM\n");
	exit(0);
}

void	handle_sigtstp(int sig)
{
	(void)sig;
	write(1, "Recibido SIGTSTP e ignorado", 28);
	ft_printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, handle_sigterm);
	signal(SIGTSTP, handle_sigtstp);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
