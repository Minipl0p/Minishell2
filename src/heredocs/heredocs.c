/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:46:35 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/06 09:57:07 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/heredocs.h"
#include <fcntl.h>

extern int	g_stop;

static int	random_name(char *buf)
{
	int		fd;
	int		i;
	char	c;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
		return (errno);
	i = 0;
	while (i < 16)
	{
		if (read(fd, &c, 1) != 1)
		{
			close(fd);
			return (errno);
		}
		buf[i] = "abcdefghijklmnopqrstuvwxyz0123456789"[(c + 256) % 36];
		i++;
	}
	buf[i] = '\0';
	close(fd);
	return (0);
}

int	open_tmp_file(char **path)
{
	char	name[17];
	int		fd;

	while (1)
	{
		if (random_name(name))
			return (-1);
		*path = ft_strjoin("/tmp/.heredoc_", name);
		if (!*path)
			return (-1);
		if (access(*path, F_OK) != 0)
			break ;
		free(*path);
	}
	fd = open(*path, O_CREAT | O_WRONLY | O_APPEND, 0600);
	if (fd < 0)
	{
		free(*path);
		return (-1);
	}
	return (fd);
}
