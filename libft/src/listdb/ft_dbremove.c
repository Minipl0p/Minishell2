/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbremove.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchazalm <pchazalm@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:25:53 by pchazalm          #+#    #+#             */
/*   Updated: 2025/12/30 19:33:19 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ft_listdb.h"

void	ft_dbremove(t_db **lst, t_db *node, void (*del)(void *))
{
	if (!lst || !*lst || !node || !del)
		return ;
	if (node->prev)
		node->prev->next = node->next;
	else
		*lst = node->next;
	if (node->next)
		node->next->prev = node->prev;
	ft_dbdelone(node, del);
}
