/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 21:54:55 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/30 22:29:01 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/pipeline.h"

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

static int	exec_builtin(t_ast_node *cmd, t_dict *d_env,
		int (*f)(t_ast_node *, t_dict *))
{
	int	ret;

	if (apply_redirections(cmd->redirs) == -1)
	{
		dup2(0, STDIN_FILENO);
		dup2(1, STDOUT_FILENO);
		return (1);
	}
	ret = f(cmd, d_env);
	dup2(0, STDIN_FILENO);
	dup2(1, STDOUT_FILENO);
	return (ret);
}

int	exec_cmd(t_btree *ast, t_dict *d_env, t_btree *root)
{
	static int (*const	f_built_in[8])(t_ast_node *cmd, t_dict *d_env) = {
	[1] = ft_cd, [2] = ft_echo, [3] = ft_env, [4] = ft_exit,
	[5] = ft_export, [6] = ft_pwd, [7] = ft_unset};
	t_list				*cmds;
	int					ret;

	cmds = NULL;
	pipe_flatten(ast, &cmds);
	expand_flatten(cmds, d_env);
	ret = is_built_in((t_ast_node *)ast->content);
	if (ret)
	{
		ret = exec_builtin(cmds->content, d_env, f_built_in[ret]);
		free_cmd_list(cmds);
		return (ret);
	}
	ret = run_pipeline(cmds, d_env, root);
	return (ret);
}
