/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:49:03 by pcaplat           #+#    #+#             */
/*   Updated: 2026/01/19 17:39:24 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lex.h"

static int	get_quoted_len(char *input, char c)
{
	int	len;

	len = 1;
	while (input[len] && input[len] != c)
		len++;
	if (!input[len])
		return (-1);
	len++;
	return (len);
}

static int	check_word_sep(char c)
{
	if (!ft_isspace(c) && c != '\'' && c != '\"' && c != ')'
		&& c != '<' && c != '>' && c != '|')
		return (1);
	return (0);
}

static int	set_word_len(char *input)
{
	int	len;
	int	end;

	len = 0;
	end = 0;
	while (!end)
	{
		if (input[len] == '\'' || input[len] == '\"')
		{
			if (input[len] == '\"')
				len += get_quoted_len(&input[len], '\"');
			else if (input[len] == '\'')
				len += get_quoted_len(&input[len], '\'');
			if (len == -1)
				return (-1);
		}
		while (input[len] && check_word_sep(input[len]))
			len++;
		if (!input[len] || is_token(&input[len]))
			end = 1;
	}
	return (len);
}

int	is_token(char *c)
{
	if (c[0] == '<' || c[0] == '>' || c[0] == '(' || c[0] == ')'
		|| c[0] == '|' || ft_isspace(c[0]))
		return (1);
	else if (c[0] == '&' && c[1] == '&')
		return (1);
	return (0);
}

char	*set_value(char **input)
{
	char	*value;
	int		len;

	if (!input || !*input)
		return (0);
	while (*input && ft_isspace(**input))
		(*input)++;
	len = set_word_len(*input);
	if (len == -1)
		return (NULL);
	value = ft_strndup(*input, len);
	(*input) += len;
	return (value);
}
