/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchazalm <pchazalm@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 19:43:16 by pchazalm          #+#    #+#             */
/*   Updated: 2025/12/30 16:18:42 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ft_io.h"

void	ft_putnb(int nb, int fd)
{
	if (nb >= 10)
	{
		ft_putnb(nb / 10, fd);
		ft_putnb(nb % 10, fd);
	}
	else
		ft_putchar_fd((nb + '0'), fd);
}

void	ft_putnbr_fd(int nb, int fd)
{
	if (!fd)
		return ;
	if (nb == -2147483648)
		write(fd, "-2147483648", 11);
	else if (nb < 0)
	{
		nb = nb * (-1);
		ft_putchar_fd('-', fd);
		ft_putnb(nb, fd);
	}
	else
		ft_putnb(nb, fd);
}
