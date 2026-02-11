/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 18:05:25 by pcaplat           #+#    #+#             */
/*   Updated: 2026/02/11 14:28:13 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lex.h"

int	create_token(t_token **token_lst, t_token_type type, char *content)
{
	t_token	*token;

	if (!*token_lst)
	{
		*token_lst = new_token(type, content);
		if (!*token_lst)
			return (-1);
		return (0);
	}
	token = new_token(type, content);
	if (!token)
		return (-1);
	add_token(token_lst, token);
	return (0);
}
