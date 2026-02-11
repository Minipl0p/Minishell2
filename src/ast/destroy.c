/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 11:59:12 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/11 14:10:32 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ast.h"

void	free_redirs(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->target);
		free(redir->delim);
		free(redir);
		redir = tmp;
	}
}

void	ast_cmd_free(t_ast_node *cmd)
{
	if (!cmd)
		return ;
	if (cmd->argv)
		ft_free_arr((void **)cmd->argv);
	free_redirs(cmd->redirs);
	free(cmd);
}

void	ast_node_free(void *content)
{
	t_ast_node	*node;

	node = (t_ast_node *)content;
	if (!node)
		return ;
	if (node->type == AST_COMMAND)
		ast_cmd_free(node);
	else
		free(node);
}
