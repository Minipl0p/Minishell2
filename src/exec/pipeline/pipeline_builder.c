/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_builder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 14:15:38 by pcaplat           #+#    #+#             */
/*   Updated: 2026/01/22 20:06:07 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"
#include <fcntl.h>

void	free_cmd_list(t_list *lst)
{
	t_list	*next;

	while (lst)
	{
		next = lst->next;
		if (lst)
			free(lst);
		lst = next;
	}
}

static int	add_to_list(t_ast_node *leaf, t_list **cmds)
{
	t_list	*cmd;

	if (!*cmds)
	{
		*cmds = ft_lstnew((void *)leaf);
		if (!*cmds)
			return (-1);
		return (0);
	}
	cmd = ft_lstnew((void *)leaf);
	if (!cmd)
		return (-1);
	ft_lstadd_back(cmds, cmd);
	return (0);
}

int	pipe_flatten(t_btree *ast, t_list **cmds)
{
	if (!ast)
		return (-1);
	pipe_flatten(ast->left, cmds);
	if (((t_ast_node *)ast->content)->type == AST_COMMAND)
	{
		if (add_to_list(ast->content, cmds) == -1)
			return (-1);
	}
	pipe_flatten(ast->right, cmds);
	return (0);
}

int	init_pipeline(t_pipeline *data, char **ev, t_dict *dict, t_list *cmds)
{
	int			count;
	t_list		*tmp;

	if (!dict || !cmds)
		return (-1);
	data->ev = ev;
	data->cmds = cmds;
	data->dict = dict;
	data->in_fd = -1;
	data->out_fd = -1;
	count = 0;
	tmp = cmds;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	data->cmd_count = count;
	return (0);
}
