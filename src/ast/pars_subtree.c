/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_subtree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 23:34:50 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/17 17:05:28 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ast.h"
#include "../../Includes/errors.h"

static int	check_end_subtree(t_token *token, t_btree *inside)
{
	if (!token || token->type != R_PAR)
	{
		ast_destroy(inside);
		ft_print_error(1, "missing ')'", "Syntax error");
		return (-1);
	}
	return (0);
}

t_btree	*parse_subtree(t_token **token)
{
	t_btree	*node;
	t_btree	*inside;

	if (!*token || (*token)->type != L_PAR)
		return (NULL);
	*token = (*token)->next;
	inside = create_ast(token);
	if (!inside)
	{
		ft_print_error(1, "Syntax error", "(");
		return (NULL);
	}
	if (check_end_subtree(*token, inside) < 0)
		return (NULL);
	*token = (*token)->next;
	node = ast_new(AST_SUBTREE);
	if (!node)
	{
		ast_destroy(inside);
		return (NULL);
	}
	node->left = inside;
	return (node);
}
