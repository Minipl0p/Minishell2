/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 17:17:12 by miniplop          #+#    #+#             */
/*   Updated: 2025/12/31 18:43:06 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ft_printf.h"

int	fd_printf(int fd, const char *str, ...)
{
	va_list	ap;
	int		nb;

	va_start(ap, str);
	nb = vd_printf(fd, str, ap);
	va_end(ap);
	return (nb);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		nb;

	va_start(ap, str);
	nb = vd_printf(1, str, ap);
	va_end(ap);
	return (nb);
}
