/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_write.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 11:16:24 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/21 12:04:40 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/heredocs.h"

extern int	g_stop;

static int	is_quoted(char *s)
{
	int	len;

	len = ft_strlen(s);
	if (len < 2)
		return (0);
	if (s[0] == '\'' && s[len - 1] == '\'')
		return (1);
	if (s[0] == '"' && s[len - 1] == '"')
		return (2);
	return (0);
}

static char	*clean_delim(char *target, int *expand)
{
	int		ret;
	char	*delim;

	ret = is_quoted(target);
	if (ret == 1)
	{
		delim = ft_substr(target, 1, ft_strlen(target) - 2);
		return (delim);
	}
	*expand = 1;
	if (ret == 2)
	{
		delim = ft_substr(target, 1, ft_strlen(target) - 2);
		return (delim);
	}
	delim = ft_strdup(target);
	return (delim);
}

int	write_heredoc(int fd, t_redir *redir)
{
	char	*line;
	char	*delim;

	delim = clean_delim(redir->target, &redir->expand);
	if (!delim)
		return (1);
	while (1)
	{
		line = readline("> ");
		if (!line || g_stop)
			break ;
		if (!ft_strcmp(line, delim))
			break ;
		ft_putendl_fd(line, fd);
		free(line);
	}
	free(delim);
	if (g_stop)
	{
		errno = EINTR;
		return (1);
	}
	return (0);
}
