/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:04:26 by pcaplat           #+#    #+#             */
/*   Updated: 2026/01/27 19:08:35 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"
#include <fcntl.h>

//static int	set_in_fd(t_ast_node *cmd)
//{
//	int	fd;
//
//	fd = -1;
//	if (cmd->redirs->type == R_IN)
//	{
//		fd = open(cmd->redirs->target, O_RDONLY);
//		if (fd == -1)
//			return (-1);
//	}
//	else if (cmd->redirs->type == R_HEREDOC)
//	{
//		fd = open(cmd->redirs->target, O_RDONLY);
//		if (fd == -1)
//			return (-1);
//	}
//	return (fd);
//}
//
//static int	set_out_fd(t_ast_node *cmd)
//{
//	int	fd;
//
//	fd = -1;
//	if (cmd->redirs->type == R_OUT)
//	{
//		fd = open(cmd->redirs->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//		if (fd == -1)
//			return (-1);
//	}
//	else if (cmd->redirs->type == R_APPEND)
//	{
//		fd = open(cmd->redirs->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
//		if (fd == -1)
//			return (-1);
//	}
//	return (fd);
//}
//
//void	set_fds(t_pipeline *data, t_list *cmds)
//{
//	t_ast_node	*cmd;
//
//	cmd = ((t_ast_node *)cmds->content);
//	if (cmd->redirs)
//	{
//		if (data->in_fd > 0)
//			close(data->in_fd);
//		data->in_fd = set_in_fd(cmd);
//		if (data->out_fd > 1)
//			close(data->out_fd);
//		data->out_fd = set_out_fd(cmd);
//		data->p_fd[0] = -1;
//		data->p_fd[1] = -1;
//	}
//}

static int	set_redir_fd(t_pipeline *data, t_redir *redir)
{
	if (redir->type == R_IN || redir->type == R_HEREDOC)
	{
		if (data->in_fd > 2)
			close(data->in_fd);
		data->in_fd = open(redir->target, O_RDONLY);
		if (data->in_fd == -1)
			return (-1);
	}
	else if (redir->type == R_OUT)
	{
		if (data->out_fd > 2)
			close(data->out_fd);
		data->out_fd = open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (data->out_fd == -1)
			return (-1);
	}
	else if (redir->type == R_APPEND)
	{
		if (data->out_fd > 2)
			close(data->out_fd);
		data->out_fd = open(redir->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (data->out_fd == -1)
			return (-1);
	}

	return (0);
}

int	set_fds(t_pipeline *data, t_list *cmds)
{
	t_redir	*redirs;

	data->in_fd = -1;
	data->out_fd = -1;
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
