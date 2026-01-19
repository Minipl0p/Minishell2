/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_printf.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchazalm <pchazalm@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:19:47 by pchazalm          #+#    #+#             */
/*   Updated: 2025/12/31 17:20:13 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ft_printf.h"

int	ft_putnbr_base_printf(unsigned long n, char *base, int fd)
{
	int				len;
	int				nb;
	unsigned long	b;

	nb = 0;
	len = ft_strlen(base);
	if (n >= (unsigned long)len)
		nb += ft_putnbr_base_printf(n / len, base, fd);
	b = n % len;
	nb += ft_putchar_printf(base[b], fd);
	return (nb);
}
