/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 21:54:55 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/16 15:16:43 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/pipeline.h"

static int	unforkable_builtin(t_ast_node *cmd, t_dict *d_env,
		int (*f)(t_ast_node *, t_dict *))
{
	t_redir	*head;
	int		fd;

	head = cmd->redirs;
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
		close(fd);
		head = head->next;
	}
	fd = f(cmd, d_env);
	return (fd);
}

int	is_forkable(t_ast_node *cmd)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	if (!ft_strcmp(cmd->argv[0], "pwd"))
		return (1);
	if (!ft_strcmp(cmd->argv[0], "env"))
		return (2);
	if (!ft_strcmp(cmd->argv[0], "echo"))
		return (3);
	if ((!ft_strcmp(cmd->argv[0], "export")) && !cmd->argv[1])
		return (4);
	else if (!ft_strcmp(cmd->argv[0], "export"))
		return (5);
	if (!ft_strcmp(cmd->argv[0], "cd"))
		return (6);
	if (!ft_strcmp(cmd->argv[0], "exit"))
		return (7);
	if (!ft_strcmp(cmd->argv[0], "unset"))
		return (8);
	return (0);
}

int	exec_cmd(t_btree *ast, t_dict *d_env, t_btree *root)
{
	static int (*const	f_built_in[9])(t_ast_node *cmd, t_dict *d_env) = {
	[1] = ft_pwd,
	[2] = ft_env,
	[3] = ft_echo,
	[4] = ft_export_no_args,
	[5] = ft_export,
	[6] = ft_cd,
	[7] = ft_exit,
	[8] = ft_unset};
	t_list				*cmds;
	int					ret;

	cmds = NULL;
	pipe_flatten(ast, &cmds);
	expand_flatten(cmds, d_env);
	ret = is_forkable((t_ast_node *)cmds->content);
	if (ret >= 5 && !cmds->next)
	{
		ret = unforkable_builtin(cmds->content, d_env, f_built_in[ret]);
		free_cmd_list(cmds);
		return (ret);
	}
	ret = run_pipeline(cmds, d_env, root);
	update_return_value(ret, d_env);
	return (ret);
}
