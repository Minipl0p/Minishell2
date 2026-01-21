/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 01:05:34 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/21 12:41:25 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

typedef enum e_signals
{
	MAIN,
	HEREDOCS,
	BANNER
}			t_signals;

void	init_signal(struct sigaction *sa, struct sigaction *old_sa, int from);

#endif
