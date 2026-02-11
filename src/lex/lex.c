/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:10:54 by pcaplat           #+#    #+#             */
/*   Updated: 2026/02/11 12:03:00 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lex.h"

static int	create_redir(t_token **token_lst, char **input)
{
	t_token_type	type;

	if (!input || !*input || (*input)[0] == '\0')
		return (0);
	if ((*input)[0] == '<' && (*input)[1] == '<')
		type = REDIR_HEREDOC;
	else if ((*input)[0] == '>' && (*input)[1] == '>')
		type = REDIR_APPEND;
	else if ((*input)[0] == '<')
		type = REDIR_IN;
	else if ((*input)[0] == '>')
		type = REDIR_OUT;
	else
		return (0);
	if (type == REDIR_HEREDOC || type == REDIR_APPEND)
		(*input) += 2;
	else
		(*input)++;
	if (create_token(token_lst, type, NULL) == -1)
		return (-1);
	return (1);
}

static int	create_op_par(t_token **token_lst, char **input)
{
	int	status;

	status = 0;
	if ((*input)[0] == '(')
		status = create_token(token_lst, L_PAR, NULL);
	else if ((*input)[0] == ')')
		status = create_token(token_lst, R_PAR, NULL);
	else if ((*input)[0] == '|')
		status = create_token(token_lst, PIPE, NULL);
	else
		return (0);
	if (status == -1)
	{
		destroy_token(*token_lst);
		return (-1);
	}
	(*input)++;
	return (1);
}

static int	create_op(t_token **token_lst, char **input)
{
	int	status;

	status = 0;
	if (!input || !*input || (*input)[0] == '\0')
		return (0);
	if ((*input)[0] == '&' && (*input)[1] == '&')
		status = create_token(token_lst, AND, NULL);
	else if ((*input)[0] == '|' && (*input)[1] == '|')
		status = create_token(token_lst, OR, NULL);
	else
		return (0);
	if (status == -1)
	{
		destroy_token(*token_lst);
		return (-1);
	}
	(*input) += 2;
	return (1);
}

static int	create_word(t_token **token_lst, char **input)
{
	char	*value;

	if (!input || !*input || (*input)[0] == '\0')
		return (0);
	else if (is_token(*input))
		return (0);
	value = set_value(input);
	if (!value)
	{
		destroy_token(*token_lst);
		return (-1);
	}
	if (create_token(token_lst, WORD, value) == -1)
	{
		destroy_token(*token_lst);
		return (-1);
	}
	return (1);
}

t_token	*lex(char *input)
{
	t_token	*token_lst;

	token_lst = NULL;
	if (!input)
		return (NULL);
	while (*input)
	{
		while (input && ft_isspace(*input))
			input++;
		if (create_redir(&token_lst, &input) == -1)
			return (NULL);
		if (create_op(&token_lst, &input) == -1)
			return (NULL);
		if (create_op_par(&token_lst, &input) == -1)
			return (NULL);
		if (create_word(&token_lst, &input) == -1)
			return (NULL);
	}
	if (create_token(&token_lst, EOF_TOK, NULL) == -1)
		return (NULL);
	return (token_lst);
}
