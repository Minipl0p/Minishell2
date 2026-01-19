/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbinsert_idx.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchazalm <pchazalm@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:05:54 by pchazalm          #+#    #+#             */
/*   Updated: 2025/12/30 19:19:46 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ft_listdb.h"

void	ft_dbinsert_idx(t_db **lst, t_db *new, int idx)
{
	t_db	*current;
	int		i;

	if (!lst || !new || idx < 0)
		return ;
	if (!*lst || idx == 0)
	{
		ft_dbadd_front(lst, new);
		return ;
	}
	if (idx >= ft_dbsize(*lst))
	{
		ft_dbadd_back(lst, new);
		return ;
	}
	current = *lst;
	i = -1;
	while (++i < idx)
		current = current->next;
	new->prev = current->prev;
	new->next = current;
	if (current->prev)
		current->prev->next = new;
	current->prev = new;
}
