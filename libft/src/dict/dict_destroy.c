/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 15:10:49 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/14 15:33:18 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ft_dict.h"

void	dict_destroy(t_dict *dict, void (*del)(void *))
{
	if (!dict)
		return ;
	dict_clear(dict, del);
	free(dict->bucket);
	free(dict);
}
