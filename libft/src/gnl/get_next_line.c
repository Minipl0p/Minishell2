/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchazalm <pchazalm@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 18:21:16 by pchazalm          #+#    #+#             */
/*   Updated: 2025/12/30 16:58:39 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ft_gnl.h"

static char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*tmp;
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	len1 = ft_strlen_gnl(s1);
	len2 = ft_strlen_gnl(s2);
	tmp = ft_calloc_gnl(sizeof(char), (len1 + len2 + 1));
	if (!tmp)
	{
		free(s1);
		return (NULL);
	}
	i = -1;
	while (++i < len1)
		tmp[i] = s1[i];
	j = 0;
	while (j < len2)
		tmp[i++] = s2[j++];
	tmp[i] = '\0';
	free(s1);
	return (tmp);
}

static char	*ft_line(char **save, char *buff)
{
	char	*line;
	char	*n_save;
	int		nl;

	free(buff);
	if (!*save || **save == '\0')
	{
		free(*save);
		*save = NULL;
		return (NULL);
	}
	nl = ft_strchr_gnl(*save, '\n');
	if (nl == -1)
	{
		line = ft_strdup_gnl(*save);
		free(*save);
		*save = NULL;
		return (line);
	}
	line = ft_substr_gnl(*save, 0, nl + 1);
	n_save = ft_strdup_gnl(*save + nl + 1);
	free(*save);
	*save = n_save;
	return (line);
}

static int	ft_read(int fd, char *buffer, char **save)
{
	int	bytes;

	bytes = read(fd, buffer, 1024);
	if (bytes == -1)
	{
		free(buffer);
		free(*save);
		*save = NULL;
	}
	return (bytes);
}

char	*get_next_line(int fd)
{
	static char	*save[1024] = {NULL};
	char		*buffer;
	char		*n_line;
	ssize_t		bytes;

	if (fd < 0 || fd > 1024 || 1024 <= 0)
		return (NULL);
	buffer = ft_calloc_gnl(sizeof(char), 1024 + 1);
	if (!buffer)
		return (NULL);
	while (ft_strchr_gnl(save[fd], '\n') < 0)
	{
		bytes = ft_read(fd, buffer, &save[fd]);
		if (bytes == -1)
			return (NULL);
		if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		save[fd] = ft_strjoin_free(save[fd], buffer);
		if (!save[fd])
			return (NULL);
	}
	n_line = ft_line(&save[fd], buffer);
	return (n_line);
}
