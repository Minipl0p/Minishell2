/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vd_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchazalm <pchazalm@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:09:24 by pchazalm          #+#    #+#             */
/*   Updated: 2025/12/31 18:53:31 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ft_printf.h"

static int	ft_percent_p(void *p, int fd)
{
	int	nb;

	nb = 0;
	if (!p)
		nb += ft_putstr_printf("(nil)", 0, fd);
	else
	{
		nb += ft_putstr_printf("0x", 0, fd);
		nb += ft_putnbr_base_printf((unsigned long)p, "0123456789abcdef", fd);
	}
	return (nb);
}

static int	ft_percent_nb(char c, va_list args, int fd)
{
	int				nb;
	unsigned int	u;

	nb = 0;
	if (c == 'd' || c == 'i')
		nb += ft_putnbr_printf(va_arg(args, int), fd);
	else if (c == 'u')
		nb += ft_putnbr_base_printf(va_arg(args, unsigned int),
				"0123456789", fd);
	else if (c == 'x')
	{
		u = va_arg(args, unsigned int);
		nb += ft_putnbr_base_printf(u, "0123456789abcdef", fd);
	}
	else if (c == 'X')
	{
		u = va_arg(args, unsigned int);
		nb += ft_putnbr_base_printf(u, "0123456789ABCDEF", fd);
	}
	else
		ft_putchar_printf(fd, c);
	return (nb);
}

static int	ft_percent(int fd, char c, va_list args)
{
	int	nb;

	nb = 0;
	if (c == 'c')
		nb += ft_putchar_printf(fd, (char)va_arg(args, int));
	else if (c == 's')
		nb += ft_putstr_printf(va_arg(args, char *), 0, fd);
	else if (c == '%')
		nb += ft_putchar_printf(fd, '%');
	else if (c == 'p')
		nb += ft_percent_p(va_arg(args, void *), fd);
	else
		nb += ft_percent_nb(c, args, fd);
	return (nb);
}

int	vd_printf(int fd, const char *str, va_list args)
{
	int		nb;
	int		i;

	nb = 0;
	while (*str)
	{
		i = 0;
		while (str[i] && str[i] != '%')
			i++;
		nb += ft_putstr_printf(str, i, fd);
		str = str + i;
		if (!*str)
			break ;
		else
		{
			str++;
			if (!*str)
				break ;
			nb += ft_percent(fd, *str, args);
			str++;
			if (!*str)
				break ;
		}
	}
	return (nb);
}
