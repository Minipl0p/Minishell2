/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 21:40:03 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/11 14:10:36 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ast.h"

void	ast_destroy(t_btree *root)
{
	t_ast_node	*new;

	if (!root)
		return ;
	ast_destroy(root->left);
	ast_destroy(root->right);
	new = root->content;
	if (new)
	{
		if (new->argv)
			ft_free_arr((void **)new->argv);
		if (new->redirs)
			free_redirs(new->redirs);
		free(new);
	}
	free(root);
}

t_btree	*ast_link_binary(t_ast_type type, t_btree *left, t_btree *right)
{
	t_btree	*node;

	node = ast_new(type);
	if (!node)
		return (NULL);
	node->left = left;
	node->right = right;
	return (node);
}

t_btree	*ast_new(t_ast_type type)
{
	t_btree		*new_tree;
	t_ast_node	*new_node;

	new_tree = ft_calloc(1, sizeof(t_btree));
	if (!new_tree)
		return (NULL);
	new_node = ft_calloc(1, sizeof(t_ast_node));
	if (!new_node)
	{
		free(new_tree);
		return (NULL);
	}
	new_node->type = type;
	new_tree->content = new_node;
	return (new_tree);
}
