/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonlogin <tonlogin@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 09:50:04 by tonlogin          #+#    #+#             */
/*   Updated: 2025/12/30 16:09:46 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ft_string.h"
#include "../../Includes/ft_utils.h"

static int	ft_lenword(char const *s, char sep)
{
	int	n;

	n = 0;
	while (s[n] && s[n] != sep)
		n++;
	return (n);
}

static char	**ft_checkarr(char const *s, char c)
{
	char	**arr;

	if (!s)
		return (NULL);
	arr = malloc(sizeof(char *) * (ft_countwordsep(s, c) + 1));
	if (!arr)
		return (NULL);
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		in[2];

	in[0] = 0;
	arr = ft_checkarr(s, c);
	if (!arr)
		return (NULL);
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		in[1] = ft_lenword(s, c);
		if (in[1] > 0)
		{
			arr[in[0]] = ft_strndup(s, in[1]);
			if (!arr[in[0]++])
			{
				ft_free_arr((void **)arr);
				return (NULL);
			}
		}
		s += in[1];
	}
	arr[in[0]] = NULL;
	return (arr);
}
