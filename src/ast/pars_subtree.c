/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_subtree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 23:34:50 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/16 14:33:43 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ast.h"

t_btree	*parse_subtree(t_token **token)
{
	t_btree	*node;
	t_btree	*inside;

	if (!*token || (*token)->type != L_PAR)
		return (parse_error("unexpected token"));
	*token = (*token)->next;
	inside = parse_or(token);
	if (!inside)
		return (NULL);
	if (!*token || (*token)->type != R_PAR)
	{
		ast_destroy(inside);
		return (parse_error("missing ')'"));
	}
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
