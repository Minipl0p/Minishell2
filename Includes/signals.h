/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 01:05:34 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/23 23:28:55 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <stdio.h>
# include <readline/readline.h>
# include <unistd.h>
# include <sys/ioctl.h>
# include <signal.h>

typedef enum e_signals
{
	MAIN,
	HEREDOCS,
	BANNER
}			t_signals;

void	init_signal(struct sigaction *sa, struct sigaction *old_sa, int from);

#endif
