/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_remove.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 16:04:39 by miniplop          #+#    #+#             */
/*   Updated: 2025/12/31 18:50:38 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ft_dict.h"

static int	rem(t_dict *dict, size_t idx, const char *key, void (*del)(void *))
{
	t_dict_entry	*entry;
	t_dict_entry	*prev;

	entry = dict->bucket[idx];
	prev = NULL;
	while (entry)
	{
		if (!ft_strcmp(entry->key, key))
		{
			if (prev)
				prev->next = entry->next;
			else
				dict->bucket[idx] = entry->next;
			if (del)
				del(entry->value);
			free(entry->key);
			free(entry);
			dict->count--;
			return (0);
		}
		prev = entry;
		entry = entry->next;
	}
	return (-1);
}

int	dict_remove(t_dict *dict, const char *key, void (*del)(void *))
{
	size_t	index;
	int		ret;

	if (!dict || !key)
		return (-1);
	index = dict_hash(key, dict->size);
	ret = rem(dict, index, key, del);
	return (ret);
}
