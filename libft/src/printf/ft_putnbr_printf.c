/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_printf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchazalm <pchazalm@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:21:26 by pchazalm          #+#    #+#             */
/*   Updated: 2025/12/31 17:19:20 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ft_printf.h"

int	ft_putnbr_printf(int nb, int fd)
{
	int	n;

	n = 0;
	if (nb == -2147483648)
	{
		n += write(1, "-2147483648", 11);
		return (n);
	}
	if (nb < 0)
	{
		nb = nb * (-1);
		n += ft_putchar_printf(fd, '-');
	}
	if (nb >= 10)
	{
		n += ft_putnbr_printf(nb / 10, fd);
		n += ft_putnbr_printf(nb % 10, fd);
	}
	else
		n += ft_putchar_printf(nb + '0', fd);
	return (n);
}
