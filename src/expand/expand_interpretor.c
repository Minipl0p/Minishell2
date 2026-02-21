/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_interpretor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 08:48:36 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/21 17:09:50 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/expand.h"

static char	*create_new_str(char *old_str, char *key, t_dict *d_env, int pos)
{
	char	*value;
	char	*new;
	int		len_k;

	len_k = ft_strlen(key);
	value = dict_get(d_env, key);
	if (!value)
		value = "";
	new = ft_calloc(sizeof(char),
			ft_strlen(old_str) - len_k + ft_strlen(value));
	if (!new)
	{
		free(key);
		return (NULL);
	}
	ft_strlcat(new, old_str, pos);
	ft_strcat(new, value);
	ft_strcat(new, old_str + pos + len_k);
	free(old_str);
	free(key);
	return (new);
}

static char	*expand_key(char *str, int pos, t_dict *d_env)
{
	char	*new;
	char	*key;
	int		l;

	l = 0;
	if (!str[pos])
		return (str);
	if (str[pos] == '?')
	{
		l++;
		key = ft_strdup("?");
		if (!key)
			return (NULL);
	}
	else
	{
		while (str[pos + l] && (str[pos + l] == '_'
				|| ft_isalnum(str[pos + l])))
			l++;
		key = ft_strndup(&str[pos], l);
		if (!key)
			return (NULL);
	}
	new = create_new_str(str, key, d_env, pos);
	return (new);
}

char	*expand_str_vars(char *old_str, t_dict *d_env)
{
	int		i;
	int		flag;
	char	*str;

	i = -1;
	flag = 0;
	if (!old_str)
		return (NULL);
	str = ft_strdup(old_str);
	if (!str)
		return (NULL);
	while (*str && str[++i])
	{
		if (flag == 0 && (str[i] == '\'' || str[i] == '\"'))
			flag += (str[i] == '\'') + 2 * (str[i] == '\"');
		else if (flag != 1 && str[i] == '$' && str[i + 1] && str[i + 1] != '$' && str[i + 1] != '\'' && str[i + 1] != '"')
		{
			str = expand_key(str, i + 1, d_env);
			i = -1;
			continue ;
		}
		else if ((flag == 1 && str[i] == '\'') || (flag == 2 && str[i] == '\"'))
			flag -= (str[i] == '\'') + 2 * (str[i] == '\"');
		if (!str[i])
			break ;
		if (!str)
			return (NULL);
	}
	return (str);
}
