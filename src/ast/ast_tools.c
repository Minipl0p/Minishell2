/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 21:40:03 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/06 10:41:31 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ast.h"

t_btree	*parse_error(char *msg)
{
	ft_putstr_fd("minishell: syntax error: ", 2);
	ft_putendl_fd(msg, 2);
	return (NULL);
}

//free the redir's linked-list from t_ast_node
static void	free_redirs(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->delim);
		free(redir->target);
		free(redir);
		redir = tmp;
	}
}

//free the ast binary tree using postfile exploration
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

// Create a binary AST node linking a left and right subtree.
// The node represents a binary operator (OR, AND, PIPE, etc.). (NORM FUNCTION)
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

//Create a new empty node with the corresponding type given in args
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
