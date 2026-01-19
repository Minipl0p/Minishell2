/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_insert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchazalm <pchazalm@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 10:13:59 by pchazalm          #+#    #+#             */
/*   Updated: 2025/12/31 10:23:03 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ft_btree.h"

void	btree_insert(t_btree **root, void *item, int (*cmpf)(void *, void *))
{
	if (!root || !cmpf)
		return ;
	if (*root == NULL)
	{
		*root = btree_new(item);
		return ;
	}
	if (cmpf(item, (*root)->content) < 0)
		btree_insert(&(*root)->left, item, cmpf);
	else
		btree_insert(&(*root)->right, item, cmpf);
}
