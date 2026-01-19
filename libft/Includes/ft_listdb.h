/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listdb.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchazalm <pchazalm@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 15:49:34 by pchazalm          #+#    #+#             */
/*   Updated: 2025/12/30 19:39:41 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LISTDB_H
# define FT_LISTDB_H

# include <stdlib.h>

typedef struct s_db
{
	void		*content;
	struct s_db	*prev;
	struct s_db	*next;
}				t_db;

t_db	*ft_dbnew(void *content);
void	ft_dbadd_front(t_db **lst, t_db *newlst);
void	ft_dbadd_back(t_db **lst, t_db *newlst);
t_db	*ft_dblast(t_db *lst);
t_db	*ft_dbfirst(t_db *lst);
int		ft_dbsize(t_db *lst);
void	ft_dbdelone(t_db *lst, void (*del)(void *));
void	ft_dbclear(t_db **lst, void (*del)(void *));
void	ft_dbiter(t_db *lst, void (*f)(void *));
t_db	*ft_dbmap(t_db *lst, void *(*f)(void *), void (*del)(void *));

#endif
