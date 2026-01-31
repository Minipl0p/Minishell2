/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_interpretor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:52:56 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/31 19:30:09 by miniplop         ###   ########.fr       */
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

char	*expand_str(char *str, t_dict *d_env)
{
	int		i;
	int		flag;
	char	*new;

	i = 0;
	flag = 0;
	if (!str)
		return (NULL);
	new = ft_strdup(str);
	while (new[i])
	{
		if (flag == 0 && (new[i] == '\'' || new[i] == '"'))
			flag += (new[i] == '\'') + 2 * (new[i] == '"');
		else if (flag != 1 && new[i] == '$')
			new = expand_key(new, i + 1, d_env);
		else if ((flag == 1 && new[i] == '\'')
				|| (flag == 2 && new[i] == '\"'))
			flag -= (new[i] == '\'') + 2 * (new[i] == '"');
		else
			i++;
		if (!new)
			return (NULL);
	}
	return (new);
}
