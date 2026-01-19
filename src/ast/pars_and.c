/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_and.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 22:44:18 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/16 14:40:27 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ast.h"

// Check if a token can legally appear after a logical AND operator.
// After '&&', the next token must start a command and cannot be
// another operator, a closing parenthesis, or EOF.
static int	is_valid_token(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == OR || token->type == AND
		|| token->type == EOF_TOK || token->type == PIPE
		|| token->type == R_PAR)
		return (0);
	return (1);
}

// Parse one '&&' operation.
// Consumes the AND token, checks syntax validity, parses the right side,
// and builds a new AST_AND node linking both subtrees.
static t_btree	*pars_and_step(t_btree *left, t_token **token)
{
	t_btree	*right;
	t_btree	*node;

	*token = (*token)->next;
	if (!is_valid_token(*token))
	{
		ast_destroy(left);
		return (parse_error("invalid &&"));
	}
	right = parse_pipe(token);
	if (!right)
	{
		ast_destroy(left);
		return (NULL);
	}
	node = ast_link_binary(AST_AND, left, right);
	if (!node)
	{
		ast_destroy(left);
		ast_destroy(right);
		return (NULL);
	}
	return (node);
}

t_btree	*parse_and(t_token **token)
{
	t_btree	*left;
	t_btree	*node;

	left = parse_pipe(token);
	while (*token && (*token)->type == AND)
	{
		left = pars_and_step(left, token);
		if (!left)
			return (NULL);
	}
	return (left);
}
