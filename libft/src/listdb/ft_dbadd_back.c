/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbadd_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchazalm <pchazalm@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:05:54 by pchazalm          #+#    #+#             */
/*   Updated: 2025/12/30 18:44:29 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ft_listdb.h"

void	ft_dbadd_back(t_db **lst, t_db *newlst)
{
	t_db	*last;

	if (!lst || !newlst)
		return ;
	newlst->next = NULL;
	if (!*lst)
	{
		newlst->prev = NULL;
		*lst = newlst;
		return ;
	}
	last = ft_dblast(*lst);
	last->next = newlst;
	newlst->prev = last;
}
