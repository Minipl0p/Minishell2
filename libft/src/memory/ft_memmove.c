/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonlogin <tonlogin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:24:19 by tonlogin          #+#    #+#             */
/*   Updated: 2025/10/23 12:46:32 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*des;
	const unsigned char	*sr;

	des = (unsigned char *)dest;
	sr = (const unsigned char *)src;
	if (des > sr)
	{
		while (n-- > 0)
		{
			des[n] = sr[n];
		}
	}
	else
	{
		i = 0;
		while (i < n)
		{
			des[i] = sr[i];
			i++;
		}
	}
	return ((void *)des);
}
