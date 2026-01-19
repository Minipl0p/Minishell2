/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 01:56:21 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/14 11:51:53 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ft_btree.h"

void	btree_clear(t_btree **root, void (*del)(void *))
{
	if (!root || !*root)
		return ;
	btree_clear(&(*root)->left, del);
	btree_clear(&(*root)->right, del);
	if (del)
		del((*root)->content);
	free(*root);
}
