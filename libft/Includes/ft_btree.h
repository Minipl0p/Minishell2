/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchazalm <pchazalm@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 09:38:45 by pchazalm          #+#    #+#             */
/*   Updated: 2026/01/14 02:05:26 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BTREE_H
# define FT_BTREE_H

# include <stdlib.h>

typedef struct s_btree
{
	void			*content;
	struct s_btree	*left;
	struct s_btree	*right;
}				t_btree;

t_btree	*btree_new(void *content);
void	btree_prefix(t_btree *root, void (*f)(void *));
void	btree_infix(t_btree *root, void (*f)(void *));
void	btree_postfix(t_btree *root, void (*f)(void *));
void	btree_clear(t_btree **root, void (*del)(void *));
void	btree_insert(t_btree **root, void *item, int (*cmpf)(void *, void *));
void	*btree_search(t_btree *root, void *data, int (*cmpf)(void *, void *));

#endif
