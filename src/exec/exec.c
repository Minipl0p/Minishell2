/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 18:01:37 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/16 10:44:20 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/pipeline.h"

static int	exec_pipeline(t_btree *ast, t_dict *d_env, t_btree *root)
{
	t_list	*cmds;
	int		ret;

	cmds = NULL;
	pipe_flatten(ast, &cmds);
	expand_flatten(cmds, d_env);
	ret = run_pipeline(cmds, d_env, root);
	update_return_value(ret, d_env);
	return (ret);
}

static int	exec_and(t_btree *ast, t_dict *d_env, t_btree *root)
{
	int	status;

	status = exec_ast(ast->left, d_env, root);
	if (status == 0)
	{
		status = exec_ast(ast->right, d_env, root);
		return (status);
	}
	return (status);
}

static int	exec_or(t_btree *ast, t_dict *d_env, t_btree *root)
{
	int	status;

	status = exec_ast(ast->left, d_env, root);
	if (status != 0)
	{
		status = exec_ast(ast->right, d_env, root);
		return (status);
	}
	return (status);
}

static int	exec_subtree(t_btree *ast, t_dict *d_env, t_btree *root)
{
	int	pid;
	int	ret;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		ret = exec_ast(ast->left, d_env, root);
		ast_destroy(root);
		dict_destroy(d_env, free);
		exit(ret);
	}
	waitpid(pid, &ret, 0);
	if (WIFEXITED(ret))
		ret = WEXITSTATUS(ret);
	else if (WIFSIGNALED(ret))
		ret = 128 + WTERMSIG(ret);
	update_return_value(ret, d_env);
	return (ret);
}

int	exec_ast(t_btree *ast, t_dict *d_env, t_btree *root)
{
	int	ret;

	if (!ast)
		return (0);
	ret = 0;
	if (((t_ast_node *)ast->content)->type == AST_PIPE)
		ret = exec_pipeline(ast, d_env, root);
	if (((t_ast_node *)ast->content)->type == AST_COMMAND)
		ret = exec_cmd(ast, d_env, root);
	if (((t_ast_node *)ast->content)->type == AST_OR)
		ret = exec_or(ast, d_env, root);
	if (((t_ast_node *)ast->content)->type == AST_AND)
		ret = exec_and(ast, d_env, root);
	if (((t_ast_node *)ast->content)->type == AST_SUBTREE)
		ret = exec_subtree(ast, d_env, root);
	return (ret);
}
