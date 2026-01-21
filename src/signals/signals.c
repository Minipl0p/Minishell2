/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 01:04:39 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/21 12:48:09 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/signals.h"
#include <stdio.h>
#include <readline/readline.h>
#include <unistd.h>

volatile int g_stop = 0;

static void	handler_banner(int sig)
{
	(void)sig;
	g_stop = 1;
}

static void	handler_main(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	handler_heredocs(int sig)
{
	g_stop = 1;
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
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
		sa->sa_flags = 0;
		sigaction(SIGQUIT, sa, NULL);
	}
	sigaction(SIGINT, sa, old_sa);
}
