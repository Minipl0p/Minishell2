/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_write.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 11:16:24 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/18 09:33:06 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/heredocs.h"
#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>

extern int	g_stop;

void	unlink_all(t_btree *ast)
{
	t_ast_node	*cmd;
	t_redir		*head;

	if (!ast)
		return ;
	unlink_all(ast->left);
	cmd = ast->content;
	if (cmd->type == AST_COMMAND)
	{
		head = cmd->redirs;
		while (head)
		{
			if (head->type == R_HEREDOC && head->target)
				unlink(head->target);
			head = head->next;
		}
	}
	unlink_all(ast->right);
}

int	write_heredoc(int fd, t_redir *redir)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || g_stop == 1)
			break ;
		if (!ft_strcmp(line, redir->delim))
			break ;
		ft_putendl_fd(line, fd);
		free(line);
	}
	free(line);
	if (g_stop == 1)
		return (130);
	return (0);
}
