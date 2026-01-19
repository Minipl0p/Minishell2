/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchazalm <pchazalm@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 15:49:15 by pchazalm          #+#    #+#             */
/*   Updated: 2025/12/31 17:21:31 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include "ft_string.h"

int	vd_printf(int fd, const char *str, va_list args);
int	fd_printf(int fd, const char *str, ...);
int	ft_printf(const char *format, ...);
int	ft_putchar_printf(int fd, char c);
int	ft_putstr_printf(const char *s, int len, int fd);
int	ft_putnbr_printf(int n, int fd);
int	ft_putnbr_base_printf(unsigned long n, char *base, int fd);

#endif
