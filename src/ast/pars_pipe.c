/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 22:56:01 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/17 10:46:05 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ast.h"
#include "../../Includes/errors.h"

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

static t_btree	*pars_pipe_step(t_btree *left, t_token **token)
{
	t_btree	*right;
	t_btree	*node;

	*token = (*token)->next;
	if (!is_valid_token(*token))
	{
		ast_destroy(left);
		ft_print_error(1, "Syntax error", "|");
		return (NULL);
	}
	right = parse_cmd(token);
	if (!right)
	{
		ast_destroy(left);
		return (NULL);
	}
	node = ast_link_binary(AST_PIPE, left, right);
	if (!node)
	{
		ast_destroy(left);
		ast_destroy(right);
		return (NULL);
	}
	return (node);
}

t_btree	*parse_pipe(t_token **token)
{
	t_btree	*left;

	left = parse_cmd(token);
	if (!left)
		return (left);
	while (*token && (*token)->type == PIPE)
	{
		left = pars_pipe_step(left, token);
		if (!left)
			return (NULL);
	}
	return (left);
}
