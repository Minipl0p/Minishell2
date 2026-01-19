/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_postfix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchazalm <pchazalm@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 09:47:46 by pchazalm          #+#    #+#             */
/*   Updated: 2026/01/12 12:00:33 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ft_btree.h"

void	btree_postfix(t_btree *root, void (*f)(void *))
{
	if (!root || !f)
		return ;
	btree_postfix(root->left, f);
	btree_postfix(root->right, f);
	f(root->content);
}
