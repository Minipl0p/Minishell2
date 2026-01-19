/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 15:58:31 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/13 15:50:23 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ft_dict.h"

void	*dict_get(t_dict *dict, const char *key)
{
	t_dict_entry	*entry;
	size_t			index;

	if (!dict || !key)
		return (NULL);
	index = dict_hash(key, dict->size);
	entry = dict->bucket[index];
	while (entry)
	{
		if (!ft_strcmp(entry->key, key))
			return (entry->value);
		entry = entry->next;
	}
	return (NULL);
}
