/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:46:35 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/18 10:29:35 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/heredocs.h"
#include "../../Includes/errors.h"
#include <fcntl.h>

extern int	g_stop;

char	*remove_hered_quote(char *s, int i)
{
	char	*new_string;
	int		len;

	len = ft_strlen(s);
	new_string = ft_calloc(sizeof(char), len);
	if (!new_string)
	{
		ft_print_error(1, NULL, "ft_calloc");
		return (NULL);
	}
	ft_strlcat(new_string, s, i + 1);
	ft_strcat(new_string, &s[i] + 1);
	free(s);
	return (new_string);
}

static int	random_name(char *buf)
{
	int		fd;
	int		i;
	char	c;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
	{
		ft_print_error(1, NULL, "open");
		return (errno);
	}
	i = 0;
	while (i < 16)
	{
		if (read(fd, &c, 1) != 1)
		{
			close(fd);
			ft_print_error(1, NULL, "read");
			return (errno);
		}
		buf[i] = "abcdefghijklmnopqrstuvwxyz0123456789"[(c + 256) % 36];
		i++;
	}
	buf[i] = '\0';
	close(fd);
	return (0);
}

void	wait_heredoc(struct sigaction *sa, int pid)
{
	int	catch;

	waitpid(pid, &catch, 0);
	init_signal(sa, NULL, MAIN);
	if (catch == 256)
		g_stop = 1;
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
		{
			ft_print_error(1, NULL, "malloc");
			return (-1);
		}
		if (access(*path, F_OK) != 0)
			break ;
		free(*path);
	}
	fd = open(*path, O_CREAT | O_WRONLY | O_APPEND, 0600);
	if (fd < 0)
	{
		free(*path);
		ft_print_error(1, NULL, "open");
		return (-1);
	}
	return (fd);
}
