/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dict.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/14 15:17:54 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DICT_H
# define FT_DICT_H

# include <stdlib.h>
# include "ft_string.h"

typedef struct s_dict_entry
{
	char				*key;
	void				*value;
	struct s_dict_entry	*next;
}	t_dict_entry;

typedef struct s_dict
{
	t_dict_entry	**bucket;
	size_t			size;
	size_t			count;
}	t_dict;

t_dict	*dict_create(size_t size);
void	dict_clear(t_dict *dict, void (*del)(void *));
void	dict_destroy(t_dict *dict, void (*del)(void *));
int		dict_set(t_dict *dict, char *key, void *value);
void	*dict_get(t_dict *dict, const char *key);
int		dict_remove(t_dict *dict, const char *key, void (*del)(void *));
size_t	dict_hash(const char *key, size_t size);
void	dict_iter(t_dict *dict, void (*f)(const char *key, void *value));

#endif
