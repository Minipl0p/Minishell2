/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 14:17:35 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/14 15:32:41 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ft_dict.h"

t_dict	*dict_create(size_t	size)
{
	t_dict			*dict;
	size_t			i;

	dict = malloc(sizeof(t_dict));
	if (!dict)
		return (NULL);
	dict->bucket = malloc(sizeof(t_dict_entry *) * size);
	if (!dict)
	{
		free(dict);
		return (NULL);
	}
	i = 0;
	while (i < size)
		dict->bucket[i++] = NULL;
	dict->size = size;
	dict->count = 0;
	return (dict);
}
