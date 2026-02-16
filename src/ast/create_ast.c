/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 17:21:45 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/16 10:16:41 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ast.h"
#include "../../Includes/errors.h"

static t_btree	*create_operator(t_token **token)
{
	t_btree	*new;

	new = NULL;
	if ((*token)->type == OR)
		new = ast_new(AST_OR);
	else if ((*token)->type == AND)
		new = ast_new(AST_AND);
	(*token) = (*token)->next;
	new->right = parse_pipe(token);
	return (new);
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
			if (!new)
				return (NULL);
			new->left = ast;
			ast = new;
		}
		else
		{
			new = parse_pipe(token);
			if (!new)
				return (NULL);
			ast = new;
		}
	}
	return (ast);
}
