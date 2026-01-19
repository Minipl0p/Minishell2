/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_infix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchazalm <pchazalm@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 09:47:46 by pchazalm          #+#    #+#             */
/*   Updated: 2026/01/12 11:59:41 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ft_btree.h"

void	btree_infix(t_btree *root, void (*f)(void *))
{
	if (!root || !f)
		return ;
	btree_infix(root->left, f);
	f(root->content);
	btree_infix(root->right, f);
}
