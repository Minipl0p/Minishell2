/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 19:06:35 by miniplop          #+#    #+#             */
/*   Updated: 2025/12/30 16:14:18 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ft_char.h"

static double	read_number(const char **str)
{
	double	res;

	res = 0.0;
	while (ft_isdigit(**str))
	{
		res = res * 10.0 + (**str - '0');
		(*str)++;
	}
	return (res);
}

double	ft_atof(const char *str)
{
	double	dec;
	double	res;
	int		sign;

	res = 0.0;
	dec = 1.0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	res = read_number(&str);
	if (*str == '.' || *str == ',')
	{
		str++;
		dec = read_number(&str);
		while (dec >= 1.0)
			dec *= 0.1;
		res += dec;
	}
	return (sign * res);
}
