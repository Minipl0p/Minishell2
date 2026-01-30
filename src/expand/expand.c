/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:56:20 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/30 18:53:23 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/expand.h"

static int	explore_heredocs(t_redir *head, t_dict *d_env,
		int (*f)(char **, t_dict *))
{
	int		fd;
	int		err;
	char	*line;
	int		flag;

	fd = open(head->target, O_RDWR, 0644);
	if (fd < 0)
		return (-1);
	flag = 1;
	while (flag || line)
	{
		flag = 0;
		line = get_next_line(fd);
		err = f(&line, d_env);
		if (err < 0)
		{
			free(line);
			close(fd);
			return (-1);
		}
		free(line);
	}
	close(fd);
	return (err);
}

static int	explore(t_ast_node *n, t_dict *d_env, int (*f)(char **, t_dict *))
{
	int		i;
	int		err;
	t_redir	*head;

	if (n->type != AST_COMMAND)
		return (0);
	i = -1;
	while (n->argv[++i])
	{
		err = f(&(n->argv[i]), d_env);
		if (err < 0)
			return (-1);
	}
	head = n->redirs;
	while (head)
	{
		if (head->type == R_HEREDOC)
			err = explore_heredocs(head, d_env, f);
		else
			err = f(&(head->target), d_env);
		if (err < 0)
			return (-1);
		head = head->next;
	}
	return (0);
}

int	expand_flatten(t_list *cmds, t_dict *d_env)
{
	int		err;
	t_list	*head;

	if (!cmds)
		return (0);
	head = cmds;
	while (head)
	{
		err = explore((t_ast_node *)head->content, d_env, expand_str);
		head = head->next;
	}
	return (err);
}
