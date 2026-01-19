/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbadd_front.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchazalm <pchazalm@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:25:41 by pchazalm          #+#    #+#             */
/*   Updated: 2025/12/30 18:48:24 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ft_listdb.h"

void	ft_dbadd_front(t_db **lst, t_db *newlst)
{
	if (!lst || !newlst)
		return ;
	newlst->prev = NULL;
	if (!*lst)
	{
		newlst->next = NULL;
		*lst = newlst;
		return ;
	}
	newlst->next = *lst;
	(*lst)->prev = newlst;
	*lst = newlst;
}
