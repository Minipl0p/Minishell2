/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 18:01:37 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/29 16:18:05 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

//static int	exec_cmd(t_btree *ast, t_dict *dict)
//{
//	t_list	*cmds;
//	int		ret;
//
//	cmds = NULL;
//	pipe_flatten(ast, &cmds);
//	ret = run_cmd(cmds, dict);
//	return (ret);
//}

static int	exec_pipeline(t_btree *ast, t_dict *dict)
{
	t_list	*cmds;
	int		ret;

	cmds = NULL;
	pipe_flatten(ast, &cmds);
	//expand_flatten(cmds);
	ret = run_pipeline(cmds, dict, ast);
	return (ret);
}

static int	exec_and(t_btree *ast, t_dict *dict)
{
	int	status;

	status = exec_ast(ast->left, dict);
	if (status == 0)
	{
		status = exec_ast(ast->right, dict);
		return (status);
	}
	return (status);
}

static int	exec_or(t_btree *ast, t_dict *dict)
{
	int	status;

	status = exec_ast(ast->left, dict);
	if (status != 0)
	{
		status = exec_ast(ast->right, dict);
		return (status);
	}
	return (status);
}

int	exec_cmd(t_btree *ast, t_dict *dict)
{
	static int (*const f_built_in[8])(t_btree *ast, t_dict *d_env) = {
	[1] = ft_cd,
	[2] = ft_echo,
    [3] = ft_env,
    [4] = ft_exit,
	[5] = ft_export,
	[6] = ft_pwd,
    [7] = ft_unset
	};
	t_list				*cmds;
	int					ret;

	cmds = NULL;
	ret = is_built_in((t_ast_node *)ast->content);
	if (ret)
	{
		f_built_in[ret](ast, dict);
		return (ret);
	}
	pipe_flatten(ast, &cmds);
	//expand_flatten(cmds);
	ret = run_pipeline(cmds, dict, ast);
	return (ret);
}

int	exec_ast(t_btree *ast, t_dict *dict)
{
	int	ret;

	if (!ast)
		return (0);
	ret = 0;
	if (((t_ast_node *)ast->content)->type == AST_PIPE)	
 	{
		ret = exec_pipeline(ast, dict);
		return (ret);
	}
	if (((t_ast_node *)ast->content)->type == AST_COMMAND)
	{
		ret = exec_cmd(ast, dict);
		return (ret);
	}
	if (((t_ast_node *)ast->content)->type == AST_OR)
	{
		ret = exec_or(ast, dict);
		return (ret);
	}
	if (((t_ast_node *)ast->content)->type == AST_AND)
	{
		ret = exec_and(ast, dict);
		return (ret);
	}
	if (((t_ast_node *)ast->content)->type == AST_SUBTREE)
	{
		ret = exec_ast(ast->left, dict);
		return (ret);
	}
	return (ret);
}
