/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchazalm <pchazalm@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:09:55 by pchazalm          #+#    #+#             */
/*   Updated: 2025/12/30 16:56:40 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ft_gnl.h"

int	ft_strchr_gnl(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

size_t	ft_strlen_gnl(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_substr_gnl(char *str, int start, int len)
{
	char	*tmp;
	int		i;
	int		s_len;

	if (!str)
		return (NULL);
	s_len = ft_strlen_gnl(str);
	if (start >= s_len)
		len = 0;
	if (len + start > s_len && len > 0)
		len = s_len - start;
	i = 0;
	tmp = ft_calloc_gnl(sizeof(char), len + 1);
	if (!tmp)
		return (NULL);
	while (i < len)
	{
		tmp[i] = str[i + start];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*ft_strdup_gnl(char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	tmp = ft_calloc_gnl(sizeof(char), (ft_strlen_gnl(str) + 1));
	if (!tmp)
		return (NULL);
	while (str[i])
	{
		tmp[i] = str[i];
		i++;
	}
	return (tmp);
}

void	*ft_calloc_gnl(size_t n, size_t m)
{
	unsigned char	*tmp;
	size_t			i;

	i = 0;
	if (n && 4294967295 / n < m)
		return (NULL);
	tmp = malloc(n * m);
	if (!tmp)
		return (NULL);
	while (i < n * m)
	{
		tmp[i] = '\0';
		i++;
	}
	return ((void *)tmp);
}
