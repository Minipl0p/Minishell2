/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_dict.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 14:19:38 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/30 09:54:11 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/dict.h"

static char	*build_exp_line(char *key, char *value)
{
	char	*line;
	int		len_v;

	if (!key)
		return (NULL);
	if (!value)
		len_v = 0;
	else
		len_v = ft_strlen(value);
	line = ft_calloc(sizeof(char), ft_strlen(key) + len_v + 4);
	if (!line)
		return (NULL);
	ft_strcat(line, key);
	if (value)
	{
		ft_strcat(line, "=\"");
		ft_strcat(line, value);
		ft_strcat(line, "\"");
	}
	return (line);
}

static char	*build_line(char *key, char *value, int	flag)
{
	char	*tmp;
	char	*line;
	char	*tmp2;

	if (flag == EXP)
	{
		line = build_exp_line(key, value);
		return (line);
	}
	if (!key)
		return (NULL);
	tmp = ft_strdup(key);
	if (!tmp)
		return (NULL);
	if (!value)
		return (tmp);
	tmp2 = ft_strjoin(tmp, "=");
	if (!tmp2)
	{
		free(tmp);
		return (NULL);
	}
	line = ft_strjoin(tmp2, value);
	free(tmp);
	free(tmp2);
	return (line);
}

static int	fill_env(t_dict *dict, char **env, int flag)
{
	size_t			i;
	size_t			j;
	t_dict_entry	*entry;
	char			*line;

	i = 0;
	j = 0;
	while (i < dict->size)
	{
		entry = dict->bucket[i];
		while (entry)
		{
			line = build_line(entry->key, entry->value, flag);
			if (!line)
			{
				ft_free_arr((void **)env);
				return (-1);
			}
			env[j++] = line;
			entry = entry->next;
		}
		i++;
	}
	env[j] = NULL;
	return (0);
}

char	**dict_to_env(t_dict *dict, int flag)
{
	char	**env;
	int		count;

	if (!dict)
		return (NULL);
	count = dict->count + 1;
	env = ft_calloc(sizeof(char *), (count + 1));
	if (!flag)
		return (NULL);
	if (fill_env(dict, env, flag) < 0)
		return (NULL);
	return (env);
}
