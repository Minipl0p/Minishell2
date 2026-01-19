/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_dict.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 14:19:38 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/19 16:56:09 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/Includes/libft.h"

static size_t	count_entries(t_dict *dict)
{
	size_t			i;
	size_t			count;
	t_dict_entry	*entry;

	if (!dict)
		return (0);
	i = 0;
	count = 0;
	while (i < dict->size)
	{
		entry = dict->bucket[i];
		while (entry)
		{
			count++;
			entry = entry->next;
		}
		i++;
	}
	return (count);
}

static char	*build_line(char *key, char *value)
{
	char	*tmp;
	char	*line;
	char	*tmp2;

	tmp = ft_strdup(key);
	if (!tmp)
		return (NULL);
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

static int	fill_env(t_dict *dict, char **env)
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
			line = build_line(entry->key, entry->value);
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

char	**dict_to_env(t_dict *dict)
{
	char	**env;
	int		count;

	if (!dict)
		return (NULL);
	count = count_entries(dict);
	env = ft_calloc(sizeof(char *), (count + 1));
	if (!env)
		return (NULL);
	if (fill_env(dict, env) < 0)
		return (NULL);
	return (env);
}
