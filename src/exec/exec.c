/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 18:01:37 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/26 17:52:38 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static int	exec_pipeline(t_btree *ast, char **ev, t_dict *dict)
{
	t_list	*cmds;
	int		ret;

	cmds = NULL;
	pipe_flatten(ast, &cmds);
	//expand_flatten(cmds);
	ret = run_pipeline(cmds, ev, dict);
	return (ret);
}

static int	exec_and(t_btree *ast, char **ev, t_dict *dict)
{
	int	status;

	status = exec_ast(ast->left, ev, dict);
	if (status == 0)
	{
		status = exec_ast(ast->right, ev, dict);
		return (status);
	}
	return (status);
}

static int	exec_or(t_btree *ast, char **ev, t_dict *dict)
{
	int	status;

	status = exec_ast(ast->left, ev, dict);
	if (status != 0)
	{
		status = exec_ast(ast->right, ev, dict);
		return (status);
	}
	return (status);
}

int	exec_ast(t_btree *ast, char **ev, t_dict *dict)
{
	int	ret;

	if (!ast)
		return (0);
	ret = 0;
	if (((t_ast_node *)ast->content)->type == AST_PIPE ||
		((t_ast_node *)ast->content)->type == AST_COMMAND)
 	{
		ret = exec_pipeline(ast, ev, dict);
		return (ret);
	}
	if (((t_ast_node *)ast->content)->type == AST_OR)
	{
		ret = exec_or(ast, ev, dict);
		return (ret);
	}
	if (((t_ast_node *)ast->content)->type == AST_AND)
	{
		ret = exec_and(ast, ev, dict);
		return (ret);
	}
	if (((t_ast_node *)ast->content)->type == AST_SUBTREE)
	{
		ret = exec_ast(ast->left, ev, dict);
		return (ret);
	}
	return (ret);
}
