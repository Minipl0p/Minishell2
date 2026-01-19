/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonlogin <tonlogin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 10:07:54 by tonlogin          #+#    #+#             */
/*   Updated: 2025/11/06 20:10:40 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_atoi(const char *ptr)
{
	size_t			i;
	int				sign;
	long long int	result;

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
	return ((int)(result * sign));
}
