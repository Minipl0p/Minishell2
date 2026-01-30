/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:52:56 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/30 18:53:47 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/expand.h"

static void	db_free(char *s1, char *s2)
{
	free(s1);
	free(s2);
}

static char	*expand_key(char *str, int pos, t_dict *d_env)
{
	char	*new;
	char	*value;
	char	*key;
	int		l;

	l = 0;
	while (str[pos + l] && (str[pos + l] == '_' || ft_isalnum(str[pos + l])))
		l++;
	key = ft_strndup(&str[pos], l);
	if (!key)
		return (NULL);
	value = dict_get(d_env, key);
	if (!value)
		value = "";
	new = ft_calloc(sizeof(char), ft_strlen(str) - l + ft_strlen(value));
	if (!new)
	{
		free(key);
		return (NULL);
	}
	ft_strlcat(new, str, pos);
	ft_strcat(new, value);
	ft_strcat(new, str + pos + l);
	db_free(str, key);
	return (new);
}

static char	*remove_quote(char *str, int pos)
{
	char	*new;

	if (!str)
		return (0);
	new = ft_calloc(sizeof(char), ft_strlen(str));
	if (!new)
		return (NULL);
	ft_strlcat(new, str, pos + 1);
	ft_strcat(new, str + pos + 1);
	free(str);
	return (new);
}

static void	expand_str_step(int *flag, char **str, int *i, t_dict *d_env)
{
	if (flag == 0 && ((*str)[*i] == '\'' || (*str)[*i] == '\"'))
	{
		*flag += ((*str)[*i] == '\'') + 2 * ((*str)[*i] == '\"');
		*str = remove_quote(*str, *i);
	}
	else if (*flag != 1 && (*str)[*i] == '$')
		*str = expand_key(*str, *i + 1, d_env);
	else if ((*flag == 1 && (*str)[*i] == '\'')
			|| (*flag == 2 && (*str)[*i] == '\"'))
	{
		*flag -= ((*str)[*i] == '\'') + 2 * ((*str)[*i] == '\"');
		*str = remove_quote(*str, *i);
	}
	else
		(*i)++;
}

int	expand_str(char **str, t_dict *d_env)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (!str || !(*str))
		return (-1);
	while ((*str)[i])
	{
		expand_str_step(&flag, str, &i, d_env);
		if (!*str)
			return (-1);
	}
	return (0);
}
