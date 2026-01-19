/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchazalm <pchazalm@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 20:05:14 by pchazalm          #+#    #+#             */
/*   Updated: 2025/11/06 20:10:32 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

long int	ft_atol(const char *ptr)
{
	size_t		i;
	int			sign;
	long int	result;

	result = 0;
	sign = 1;
	i = 0;
	while (ptr[i] == ' ' || ((ptr[i] >= '\t') && (ptr[i] <= '\r')))
		i++;
	if (ptr[i] == '+')
		i++;
	else if (ptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (ptr[i] >= '0' && ptr[i] <= '9')
	{
		result = 10 * result + (ptr[i] - '0');
		i++;
	}
	return ((result * sign));
}
