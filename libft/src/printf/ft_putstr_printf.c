/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_printf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchazalm <pchazalm@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:10:40 by pchazalm          #+#    #+#             */
/*   Updated: 2025/12/31 17:13:35 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ft_printf.h"

int	ft_putstr_printf(const char *s, int len, int fd)
{
	int	nb;

	if (!s)
		nb = write(fd, "(null)", 6);
	else if (len == 0)
		nb = write(fd, s, ft_strlen(s));
	else
		nb = write(fd, s, len);
	return (nb);
}
