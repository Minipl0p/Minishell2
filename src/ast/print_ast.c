/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 16:33:30 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/17 16:34:23 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ast.h"

static void	print_indent(int depth)
{
	while (depth--)
		printf("│   ");
}

static void	print_redirs(t_redir *r, int depth)
{
	while (r)
	{
		print_indent(depth);
		printf("REDIR ");
		if (r->type == R_IN) printf("< ");
		if (r->type == R_OUT) printf("> ");
		if (r->type == R_APPEND) printf(">> ");
		if (r->type == R_HEREDOC) printf("<< ");
		printf("%s\n", r->target);
		r = r->next;
	}
}

void	print_ast(t_btree *root, int depth)
{
	t_ast_node	*node;
	int			i;

	if (!root)
		return;

	node = (t_ast_node *)root->content;

	print_indent(depth);
	if (node->type == AST_COMMAND) printf("COMMAND\n");
	else if (node->type == AST_PIPE) printf("PIPE\n");
	else if (node->type == AST_AND) printf("AND\n");
	else if (node->type == AST_OR) printf("OR\n");
	else if (node->type == AST_SUBTREE) printf("SUBTREE\n");

	if (node->argv)
	{
		i = 0;
		while (node->argv[i])
		{
			print_indent(depth + 1);
			printf("ARG[%d]: %s\n", i, node->argv[i]);
			i++;
		}
	}

	if (node->redirs)
		print_redirs(node->redirs, depth + 1);

	print_ast(root->left, depth + 1);
	print_ast(root->right, depth + 1);
}
