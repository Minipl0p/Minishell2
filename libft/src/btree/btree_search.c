/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_search.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchazalm <pchazalm@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 10:25:11 by pchazalm          #+#    #+#             */
/*   Updated: 2025/12/31 10:55:52 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ft_btree.h"

void	*btree_search(t_btree *root, void *data, int (*cmpf)(void *, void *))
{
	void	*res;

	if (!root || !cmpf)
		return (NULL);
	res = btree_search(root->left, data, cmpf);
	if (res)
		return (res);
	if (cmpf(data, root->content) == 0)
		return (root->content);
	res = btree_search(root->right, data, cmpf);
	return (res);
}
