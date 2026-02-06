/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 12:03:45 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/06 10:42:43 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ast.h"

static t_redir_type	token_to_redir(t_token_type type)
{
	if (type == REDIR_IN)
		return (R_IN);
	if (type == REDIR_OUT)
		return (R_OUT);
	if (type == REDIR_APPEND)
		return (R_APPEND);
	if (type == REDIR_HEREDOC)
		return (R_HEREDOC);
	return (-1);
}

static void	redir_add_back(t_redir **lst, t_redir *new)
{
	t_redir	*cur;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	cur = *lst;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

int	parse_redir(t_token **token, t_redir **redirs)
{
	t_redir	*new;

	new = ft_calloc(1, sizeof(t_redir));
	if (!new)
		return (-1);
	new->expand = 0;
	new->next = NULL;
	new->delim = NULL;
	new->type = token_to_redir((*token)->type);
	*token = (*token)->next;
	if (!*token || (*token)->type != WORD)
	{
		free(new);
		return (-1);
	}
	new->target = ft_strdup((*token)->value);
	if (!new->target)
	{
		free(new);
		return (-1);
	}
	*token = (*token)->next;
	redir_add_back(redirs, new);
	return (0);
}
