/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 18:01:37 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/22 14:53:38 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ast.h"

int	exec(t_btree *ast);

static int	exec_pipeline(t_btree *ast)
{
	t_list	*cmds;
	int		ret;

	cmds = NULL;
	pipe_flatten(ast, &cmds);
	expand_flatten(cmds);
	ret = run_pipeline(cmds);
	return (ret);
}

static int	exec_and(t_btree *ast)
{
	int	status;

	status = exec(ast->left);
	if (status == 0)
	{
		status = exec(ast->right);
		return (status);
	}
	return (status);
}

static int	exec_or(t_btree *ast)
{
	int	status;

	status = exec(ast->left);
	if (status != 0)
	{
		status = exec(ast->right);
		return (status);
	}
	return (status);
}

int	exec(t_btree *ast)
{
	int	ret;

	if (!ast)
		return (0);
	if (((t_ast_node *)ast->content)->type == AST_PIPE || AST_COMMAND)
 	{
		ret = exec_pipeline(ast);
		return (ret);
	}
	if (((t_ast_node *)ast->content)->type == AST_OR)
	{
		ret = exec_or(ast);
		return (ret);
	}
	if (((t_ast_node *)ast->content)->type == AST_AND)
	{
		ret = exec_and(ast);
		return (ret);
	}
	if (((t_ast_node *)ast->content)->type == AST_SUBTREE)
	{
		ret = exec(ast->left);
		return (ret);
	}
}
