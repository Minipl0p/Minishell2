/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbinsert_add.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchazalm <pchazalm@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:05:54 by pchazalm          #+#    #+#             */
/*   Updated: 2025/12/30 19:21:51 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ft_listdb.h"

void	ft_dbinsert_add(t_db **lst, t_db *new, t_db *target)
{
	t_db	*current;

	if (!lst || !new || !target)
		return ;
	if (!*lst)
		return ;
	current = *lst;
	while (current && current != target)
		current = current->next;
	if (!current)
		return ;
	new->prev = current->prev;
	new->next = current;
	if (current->prev)
		current->prev->next = new;
	else
		*lst = new;
	current->prev = new;
}
