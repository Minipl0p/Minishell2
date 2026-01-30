/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:00:58 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/30 19:02:35 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lex.h"

t_token	*new_token(t_token_type type, char *content)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = content;
	token->next = NULL;
	return (token);
}

static t_token	*token_last(t_token *token_lst)
{
	if (!token_lst)
		return (NULL);
	while (token_lst->next)
		token_lst = token_lst->next;
	return (token_lst);
}

void	add_token(t_token **token_lst, t_token *token)
{
	t_token	*last;

	if (!token_lst || !token)
		return ;
	if (!*token_lst)
	{
		*token_lst = token;
		return ;
	}
	last = token_last(*token_lst);
	last->next = token;
}

void	destroy_token(t_token *token_lst)
{
	t_token	*next;

	while (token_lst)
	{
		next = token_lst->next;
		if (token_lst->value)
			free(token_lst->value);
		free(token_lst);
		token_lst = next;
	}
}
