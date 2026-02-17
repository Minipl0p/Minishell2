/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_kaam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchazalm <pchazalm@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 11:13:15 by pchazalm          #+#    #+#             */
/*   Updated: 2026/02/17 11:44:24 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/errors.h"

static char	*get_quote2(int i)
{
	if (i == 6)
		return (KQ6);
	if (i == 7)
		return (KQ7);
	if (i == 8)
		return (KQ8);
	if (i == 9)
		return (KQ9);
	if (i == 10)
		return (KQ10);
	if (i == 11)
		return (KQ11);
	else
		return (KQ12);
}

static char	*get_quote(void)
{
	static int	i = -1;

	i++;
	if (i == 0)
		return (KQ0);
	if (i == 1)
		return (KQ1);
	if (i == 2)
		return (KQ2);
	if (i == 3)
		return (KQ3);
	if (i == 4)
		return (KQ4);
	if (i == 5)
		return (KQ5);
	return (get_quote2(i));
}

void	print_kaamellot_error(void)
{
	char	*msg;

	msg = get_quote();
	ft_putstr_fd("\n\033[1;33m \"", STDOUT_FILENO);
	ft_putstr_fd(msg, STDOUT_FILENO);
	ft_putstr_fd("\"\033[0m\n\n", STDOUT_FILENO);
}
