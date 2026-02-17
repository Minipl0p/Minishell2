/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 01:04:39 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/17 18:38:22 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/signals.h"
#include <signal.h>
#include <sys/ioctl.h>
#include <unistd.h>

volatile int	g_stop = 0;

static void	handler_banner(int sig)
{
	(void)sig;
	g_stop = 1;
}

static void	handler_main(int sig)
{
	if (sig == SIGINT)
	{
		g_stop = 1;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	handler_heredocs(int sig)
{
	char	c;

	(void)sig;
	g_stop = 1;
	c = '\n';
	ioctl(STDIN_FILENO, TIOCSTI, &c);
}

void	init_signal(struct sigaction *sa, struct sigaction *old_sa, int from)
{
	g_stop = 0;
	sigemptyset(&(sa->sa_mask));
	if (from == BANNER)
	{
		sa->sa_handler = handler_banner;
		sa->sa_flags = 0;
	}
	if (from == HEREDOCS)
	{
		sa->sa_handler = handler_heredocs;
		sa->sa_flags = 0;
	}
	if (from == MAIN)
	{
		sa->sa_handler = handler_main;
		sa->sa_flags = SA_RESTART;
	}
	sigaction(SIGINT, sa, old_sa);
}
