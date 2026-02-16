/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:04:26 by pcaplat           #+#    #+#             */
/*   Updated: 2026/02/16 18:59:03 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/pipeline.h"
#include "../../../Includes/errors.h"

static int	set_out_redir(t_pipeline *data, t_redir *redir)
{
	if (redir->type == R_OUT)
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

static int	check_middle_fd(t_pipeline *data, t_redir *redir)
{
	if (data->in_fd == -1)
	{
		ft_print_error(1, NULL, redir->target);
		return (-1);
	}
	return (0);
}

static int	set_redir_fd(t_pipeline *data, t_redir *redir)
{
	char	*tmp;

	tmp = NULL;
	if (redir->type == R_IN || redir->type == R_HEREDOC)
	{
		if (data->in_fd > 2)
			close(data->in_fd);
		tmp = ft_strchr((char *)(redir->target), '$');
		if (redir->target && tmp && *(tmp + 1))
			return (-1);
		data->in_fd = open(redir->target, O_RDONLY);
		if (check_middle_fd(data, redir) < 0)
			return (-1);
	}
	else
	{
		if (data->out_fd > 2)
			close(data->out_fd);
		if (set_out_redir(data, redir) == -1)
		{
			ft_print_error(1, NULL, redir->target);
			return (-1);
		}
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
			return (-1);
		redirs = redirs->next;
	}
	return (0);
}
