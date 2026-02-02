/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:56:20 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/02 11:43:26 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/expand.h"

static int	process_node(t_ast_node *node, t_dict *env)
{
	if (!node)
		return (0);
	if (node->argv)
	{
		if (expand_argv_array(&node->argv, env) == -1)
			return (-1);
	}
	if (node->redirs)
	{
		if (expand_redir_list(node->redirs, env) == -1)
			return (-1);
	}
	return (0);
}

int	expand_flatten(t_list *cmds, t_dict *env)
{
	t_list		*current;
	t_ast_node	*node;

	current = cmds;
	while (current)
	{
		node = (t_ast_node *)current->content;
		if (node->type == AST_COMMAND)
		{
			if (process_node(node, env) == -1)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}
