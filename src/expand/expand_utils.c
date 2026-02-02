/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:52:56 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/02 09:24:37 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/expand.h"

static int	ft_lenword(char const *s, char sep)
{
	int	n;
	int	flag;

	n = 0;
	flag = 0;
	while (s[n])
	{
		if (flag == 0 && (s[n] == '\'' || s[n] == '\"'))
			flag += (s[n] == '\'') + 2 * (s[n] == '\"');
		if (s[n] && (s[n] != sep || (flag > 0 && s[n] == sep)))
			n++;
		else
			break ;
		if ((flag == 1 && s[n] == '\'') || (flag == 2 && s[n] == '\"'))
			flag -= (s[n] == '\'') + 2 * (s[n] == '\"');
	}
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

char	**split_words_nquoted(char const *s, char c)
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

static char	*remove_quote(char *str, int pos)
{
	char	*new;

	if (!str)
		return (0);
	new = ft_calloc(sizeof(char), ft_strlen(str));
	if (!new)
		return (NULL);
	ft_strlcat(new, str, pos + 1);
	ft_strcat(new, str + pos + 1);
	free(str);
	return (new);
}

