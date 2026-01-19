/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_d_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:38:09 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/13 17:30:54 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/Includes/libft.h"

static int	len_key(char *str)
{
	size_t	len;

	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	if (str[len] != '=')
		return (0);
	return (len);
}

static int	set_raw(char *raw, t_dict **d_env)
{
	size_t	len;
	char	*key;
	char	*value;

	len = len_key(raw);
	if (len > 0)
	{
		key = ft_substr(raw, 0, len);
		value = ft_strdup(raw + len + 1);
		if (!key || !value || dict_set(*d_env, key, value) < 0)
		{
			if (key)
				free(key);
			if (value)
				free(value);
			dict_destroy(*d_env, free);
			return (-1);
		}
		free(key);
	}
	return (0);
}

t_dict	*init_d_env(char **env)
{
	int		size;
	t_dict	*d_env;

	size = 0;
	if (!env)
		return (NULL);
	while (env[size])
		size++;
	d_env = dict_create(size);
	if (!d_env)
		return (NULL);
	size = 0;
	while (env[size])
	{
		if (set_raw(env[size], &d_env) < 0)
			return (NULL);
		size++;
	}
	return (d_env);
}
