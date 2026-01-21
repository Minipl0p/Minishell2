/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:46:35 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/21 12:43:44 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/heredocs.h"

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

static int	open_tmp_file(char **path)
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
	fd = open(*path, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
	{
		free(*path);
		return (-1);
	}
	return (fd);
}

static int	restore_heredoc(struct sigaction *old, char *path, int fd)
{
	if (fd >= 0)
		close(fd);
	if (path)
	{
		unlink(path);
		free(path);
	}
	sigaction(SIGINT, old, NULL);
	return (1);
}

static int	handle_heredoc(t_redir *redir)
{
	struct sigaction	sa;
	struct sigaction	old;
	char				*path;
	int					fd;

	g_stop = 0;
	init_signal(&sa, &old, HEREDOCS);
	fd = open_tmp_file(&path);
	ft_putendl_fd(path, 1);
	if (fd < 0)
	{
		restore_heredoc(&old, NULL, fd);
		return (1);
	}
	if (write_heredoc(fd, redir))
	{
		restore_heredoc(&old, path, fd);
		return (1);
	}
	close(fd);
	sigaction(SIGINT, &old, NULL);
	free(redir->target);
	redir->target = path;
	return (0);
}

int	create_heredocs(t_btree *ast)
{
	t_ast_node	*cmd;
	t_redir		*redir;

	if (!ast)
		return (0);
	if (create_heredocs(ast->left))
		return (1);
	cmd = ast->content;
	if (cmd->type == AST_COMMAND)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == R_HEREDOC)
			{
				if (handle_heredoc(redir))
					return (1);
			}
			redir = redir->next;
		}
	}
	return (create_heredocs(ast->right));
}
