/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchazalm <pchazalm@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 22:42:31 by pchazalm          #+#    #+#             */
/*   Updated: 2025/12/30 19:35:36 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ft_listdb.h"

t_db	*ft_lstmap(t_db *lst, void *(*f)(void *), void (*del)(void *))
{
	t_db	*n_list;
	t_db	*n_elem;
	void	*n_content;

	if (!lst || !f || !del)
		return (NULL);
	n_list = NULL;
	while (lst)
	{
		n_content = (*f)(lst->content);
		n_elem = ft_dbnew(n_content);
		if (!n_elem)
		{
			del(n_content);
			ft_dbclear(&n_list, del);
			return (NULL);
		}
		ft_dbadd_back(&n_list, n_elem);
		lst = lst->next;
	}
	return (n_list);
}
