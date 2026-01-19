/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_iter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 16:06:51 by miniplop          #+#    #+#             */
/*   Updated: 2025/12/31 16:08:51 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ft_dict.h"

void	dict_iter(t_dict *dict, void (*f)(const char *key, void *value))
{
	t_dict_entry	*entry;
	size_t			i;

	if (!dict || !f)
		return ;
	i = 0;
	while (i < dict->size)
	{
		entry = dict->bucket[i];
		while (entry)
		{
			f(entry->key, entry->value);
			entry = entry->next;
		}
		i++;
	}
}
