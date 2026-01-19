/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_prefix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchazalm <pchazalm@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 09:47:46 by pchazalm          #+#    #+#             */
/*   Updated: 2025/12/31 10:27:03 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ft_btree.h"

void	btree_prefix(t_btree *root, void (*f)(void *))
{
	if (!root || !f)
		return ;
	f(root->content);
	btree_prefix(root->left, f);
	btree_prefix(root->right, f);
}
