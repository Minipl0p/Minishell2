/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 18:01:37 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/30 18:21:34 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"
#include <stdio.h>
#include <unistd.h>

static int	exec_pipeline(t_btree *ast, t_dict *dict, t_btree *root)
{
	t_list	*cmds;
	int		ret;

	cmds = NULL;
	pipe_flatten(ast, &cmds);
	expand_flatten(cmds, dict);
	ret = run_pipeline(cmds, dict, root);
	return (ret);
}

static int	exec_and(t_btree *ast, t_dict *dict, t_btree *root)
{
	int	status;

	status = exec_ast(ast->left, dict, root);
	if (status == 0)
	{
		status = exec_ast(ast->right, dict, root);
		return (status);
	}
	return (status);
}

static int	exec_or(t_btree *ast, t_dict *dict, t_btree *root)
{
	int	status;

	status = exec_ast(ast->left, dict, root);
	if (status != 0)
	{
		status = exec_ast(ast->right, dict, root);
		return (status);
	}
	return (status);
}

static int	apply_redirections(t_redir *redir)
{
	int		fd;
	t_redir	*head;

	head = redir;
	while (head)
	{
		if (head->type == R_IN || head->type == R_HEREDOC)
			fd = open(head->target, O_RDONLY);
		else if (head->type == R_OUT)
			fd = open(head->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (head->type == R_APPEND)
			fd = open(head->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			perror(head->target);
			return (-1);
		}
		if (head->type == R_IN || head->type == R_HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		head = head->next;
	}
	return (0);
}

int    exec_builtin(t_ast_node *cmd, t_dict *dict, int (*f)(t_ast_node *, t_dict *))
{
	int    save_stdout;
	int    save_stdin;
	int    ret;

	save_stdout = dup(STDOUT_FILENO);
	save_stdin = dup(STDIN_FILENO);
	if (apply_redirections(cmd->redirs) == -1) 
	{
		dup2(save_stdout, STDOUT_FILENO);
		dup2(save_stdin, STDIN_FILENO);
		close(save_stdout);
		close(save_stdin);
		return (1);
	}
	ret = f(cmd, dict);
	dup2(save_stdin, STDIN_FILENO);
	close(save_stdin);
	dup2(save_stdout, STDOUT_FILENO);
	close(save_stdout);
	return (ret);
}

int	exec_cmd(t_btree *ast, t_dict *dict, t_btree *root)
{
	static int (*const f_built_in[8])(t_ast_node *cmd, t_dict *d_env) = {
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
	pipe_flatten(ast, &cmds);
	expand_flatten(cmds, dict);
	ret = is_built_in((t_ast_node *)ast->content);
	if (ret)
	{
		ret = exec_builtin(cmds->content, dict, f_built_in[ret]);
		free_cmd_list(cmds);
		return (ret);
	}
	ret = run_pipeline(cmds, dict, root);
	return (ret);
}

int	exec_ast(t_btree *ast, t_dict *dict, t_btree *root)
{
	int	ret;
	int	pid;

	if (!ast)
		return (0);
	ret = 0;
	if (((t_ast_node *)ast->content)->type == AST_PIPE)	
	{
		ret = exec_pipeline(ast, dict, root);
		return (ret);
	}
	if (((t_ast_node *)ast->content)->type == AST_COMMAND)
	{
		ret = exec_cmd(ast, dict, root);
		return (ret);
	}
	if (((t_ast_node *)ast->content)->type == AST_OR)
	{
		ret = exec_or(ast, dict, root);
		return (ret);
	}
	if (((t_ast_node *)ast->content)->type == AST_AND)
	{
		ret = exec_and(ast, dict, root);
		return (ret);
	}
	if (((t_ast_node *)ast->content)->type == AST_SUBTREE)
	{
		pid = fork();
		if (pid == -1)
			return (perror("fork"), 1);
		if (pid == 0)
		{
			ret = exec_ast(ast->left, dict, root);
			ast_destroy(root);
			dict_destroy(dict, free);
			exit(ret);
		}
		waitpid(pid, &ret, 0);
		if (WIFEXITED(ret))
			ret = WEXITSTATUS(ret);
		else if (WIFSIGNALED(ret))
			ret = 128 + WTERMSIG(ret);
		return (ret);
	}
	return (ret);
}
