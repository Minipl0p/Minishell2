/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchazalm <pchazalm@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:25:41 by pchazalm          #+#    #+#             */
/*   Updated: 2025/12/30 16:54:00 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ft_list.h"

void	ft_lstadd_front(t_list **lst, t_list *newlst)
{
	if (!lst || !newlst)
		return ;
	newlst->next = *lst;
	*lst = newlst;
}
