/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonlogin <tonlogin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:55:22 by tonlogin          #+#    #+#             */
/*   Updated: 2025/10/23 12:46:22 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

size_t	ft_strlcat(char *dest, const char *src, size_t l)
{
	size_t	l_dest;
	size_t	l_src;
	size_t	i;

	i = 0;
	l_dest = 0;
	l_src = 0;
	if (dest)
	{
		while (dest[l_dest])
			l_dest++;
	}
	while (src[l_src])
		l_src++;
	if (l <= l_dest)
		return (l + l_src);
	while (src[i] && (l_dest + i) < (l - 1))
	{
		dest[l_dest + i] = src[i];
		i++;
	}
	dest[l_dest + i] = '\0';
	return (l_dest + l_src);
}
