/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 15:42:21 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/03 15:41:41 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/expand.h"

int	check_ambiguous(t_list *lst)
{
	if (!lst || ft_lstsize(lst) != 1)
	{
		ft_putstr_fd("Minishell: ambiguous redirect\n", 2);
		return (-1);
	}
	return (0);
}

int	expand_single_redir(t_redir *redir, t_dict *d_env)
{
	t_list	*res_list;
	char	*new_target;

	if (redir->type == R_HEREDOC && redir->expand == 1)
	{
		expand_heredocs(redir, d_env);
		return (0);
	}
	res_list = NULL;
	if (process_expand(redir->target, &res_list, d_env) == -1)
		return (-1);
	if (check_ambiguous(res_list) == -1)
	{
		ft_lstclear(&res_list, free);
		return (-1);
	}
	new_target = ft_strdup((char *)res_list->content);
	free(redir->target);
	redir->target = new_target;
	ft_lstclear(&res_list, free);
	return (0);
}

int	expand_redir_list(t_redir *head, t_dict *env)
{
	t_redir	*curr;

	curr = head;
	while (curr)
	{
		if (expand_single_redir(curr, env) == -1)
			return (-1);
		curr = curr->next;
	}
	return (0);
}
