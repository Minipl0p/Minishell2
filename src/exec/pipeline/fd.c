/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:04:26 by pcaplat           #+#    #+#             */
/*   Updated: 2026/01/28 10:53:33 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

static int	set_redir_fd(t_pipeline *data, t_redir *redir)
{
	if (redir->type == R_IN || redir->type == R_HEREDOC)
	{
		data->in_fd = open(redir->target, O_RDONLY);
		if (data->in_fd == -1)
			return (-1);
	}
	else if (redir->type == R_OUT)
	{
		data->out_fd = open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (data->out_fd == -1)
			return (-1);
	}
	else if (redir->type == R_APPEND)
	{
		data->out_fd = open(redir->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (data->out_fd == -1)
			return (-1);
	}

	return (0);
}

int	set_fds(t_pipeline *data, t_list *cmds)
{
	t_redir	*redirs;

	if (data->in_fd > 2)
		close(data->in_fd);
	if (data->out_fd > 2)
		close(data->out_fd);
	redirs = ((t_ast_node *)cmds->content)->redirs;
	while (redirs)
	{
		if (set_redir_fd(data, redirs) == -1)
		{
			perror("open");
			return (-1);
		}
		redirs = redirs->next;
	}
	return (0);
}
