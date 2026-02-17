/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 17:21:45 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/17 18:03:34 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ast.h"
#include "../../Includes/errors.h"

static t_btree	*create_operator(t_token **token)
{
	t_btree		*new;
	t_ast_node	*tmp;

	new = NULL;
	if ((*token)->type == OR)
		new = ast_new(AST_OR);
	else if ((*token)->type == AND)
		new = ast_new(AST_AND);
	(*token) = (*token)->next;
	if ((*token)->type == EOF_TOK)
	{
		tmp = new->content;
		if (tmp->type == AST_OR)
			ft_print_error(1, "Syntax error", "||");
		if (tmp->type == AST_AND)
			ft_print_error(1, "Syntax error", "&&");
		return (NULL);
	}
	new->right = parse_pipe(token);
	return (new);
}

static int	safe_exit(t_btree *new, t_btree *ast)
{
	if (!new)
	{
		ast_destroy(ast);
		ast = NULL;
		return (-1);
	}
	return (0);
}

t_btree	*create_ast(t_token **token)
{
	t_btree	*ast;
	t_btree	*new;

	ast = NULL;
	while ((*token)->type != EOF_TOK && (*token)->type != R_PAR)
	{
		if ((*token)->type == OR || (*token)->type == AND)
		{
			new = create_operator(token);
			if (safe_exit(new, ast) < 0)
				return (NULL);
			new->left = ast;
			ast = new;
		}
		else
		{
			new = parse_pipe(token);
			if (safe_exit(new, ast) < 0)
				return (NULL);
			ast = new;
		}
	}
	return (ast);
}
