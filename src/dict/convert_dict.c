/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_dict.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 14:19:38 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/26 22:35:54 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/dict.h"

static char	*build_exp_line(char *key, char *value)
{
	//char	*tmp;
	char	*line;
	//char	*tmp2;

	line = ft_calloc(sizeof(char), ft_strlen(key) + ft_strlen(value) + 4);
	if (line)
		return (NULL);
	line = ft_strcat(line, key);
	if (value)
	{
		line = ft_strcat(line, "=\"");
		line = ft_strcat(line, value);
		line = ft_strcat(line, "\"");
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
	if (fill_env(dict, env, ENV) < 0)
		return (NULL);
	return (env);
}
