/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchazalm <pchazalm@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:48:08 by pchazalm          #+#    #+#             */
/*   Updated: 2025/12/30 16:15:54 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ft_string.h"

static int	ft_nbnb(int *n, int *sign)
{
	int	i;
	int	j;

	i = 0;
	if (*n < 0)
	{
		*sign = -1;
		*n *= -1;
	}
	j = *n;
	while (j > 0)
	{
		j /= 10;
		i++;
	}
	if (*sign == -1)
		i++;
	return (i);
}

static char	*ft_ifedgecase(int *n, int *flag_edge)
{
	char	*str;

	if (*n == 0)
	{
		str = malloc(sizeof(char) * 2);
		if (!str)
			return (NULL);
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	else if (*n == -2147483648)
	{
		str = ft_strdup("-2147483648");
		if (!str)
			return (NULL);
		return (str);
	}
	*flag_edge = 0;
	return (NULL);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		flag_edge;
	int		nb_nb;
	int		sign;

	sign = 1;
	flag_edge = 1;
	str = ft_ifedgecase(&n, &flag_edge);
	if (flag_edge && !str)
		return (NULL);
	if (str)
		return (str);
	nb_nb = ft_nbnb(&n, &sign);
	str = malloc(sizeof(char) * (nb_nb + 1));
	if (!str)
		return (NULL);
	if (sign == -1)
		str[0] = '-';
	str[nb_nb] = '\0';
	while ((nb_nb > 0 && sign == 1) || (nb_nb > 1 && sign == -1))
	{
		str[nb_nb-- - 1] = '0' + (n % 10);
		n /= 10;
	}
	return (str);
}
