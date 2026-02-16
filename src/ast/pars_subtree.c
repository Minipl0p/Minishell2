/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_subtree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 23:34:50 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/16 10:09:43 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ast.h"
#include "../../Includes/errors.h"

t_btree	*parse_subtree(t_token **token)
{
	t_btree	*node;
	t_btree	*inside;

	if (!*token || (*token)->type != L_PAR)
	{
		ft_print_error(1, "syntax error", "|");
		return (NULL);
	}
	*token = (*token)->next;
	inside = parse_or(token);
	if (!inside)
		return (NULL);
	if (!*token || (*token)->type != R_PAR)
	{
		ast_destroy(inside);
		ft_print_error(1, "missing ')'", "syntax error");
		return (NULL);
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
