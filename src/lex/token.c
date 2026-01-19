/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 18:05:25 by pcaplat           #+#    #+#             */
/*   Updated: 2026/01/19 13:12:44 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lex.h"

void	display_type(t_token *token_lst)
{
	if (token_lst->type == WORD)
		printf("WORD : ");
	if (token_lst->type == PIPE)
		printf("PIPE : ");
	if (token_lst->type == REDIR_IN)
		printf("REDIR_IN : ");
	if (token_lst->type == REDIR_OUT)
		printf("REDIR_OUT : ");
	if (token_lst->type == REDIR_APPEND)
		printf("REDIR_APPEND : ");
	if (token_lst->type == REDIR_HEREDOC)
		printf("REDIR_HEREDOC : ");
	if (token_lst->type == OR)
		printf("OR : ");
	if (token_lst->type == AND)
		printf("AND : ");
	if (token_lst->type == L_PAR)
		printf("L_PAR : ");
	if (token_lst->type == R_PAR)
		printf("R_PAR : ");
	if (token_lst->type == EOF_TOK)
		printf("EOF_TOK : ");
}

void	display_tokens(t_token *token_lst)
{
	t_token	*tmp;

	printf("=========TOKENS=========\n");
	tmp = token_lst;
	while (tmp)
	{
		display_type(tmp);
		if (tmp->value)
			printf("<%s>\n", tmp->value);
		else
			printf("NULL\n");
		tmp = tmp->next;
		if (tmp)
			printf("\n");
	}
}

static t_token	*token_last(t_token *token_lst)
{
	if (!token_lst)
		return (NULL);
	while (token_lst->next)
		token_lst = token_lst->next;
	return (token_lst);
}

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
