/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_d_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:38:09 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/01 11:43:40 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/dict.h"
#include <unistd.h>

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
		if (!key || !value || dict_set(*d_env, key, value, free) < 0)
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

static int	minimal_env(t_dict *d_env)
{
	char	*pwd_val;
	char	*cwd;
	char	*exit_status;

	pwd_val = dict_get(d_env, "PWD");
	if (pwd_val == NULL)
	{
		cwd = getcwd(NULL, 0);
		if (cwd)
			dict_set(d_env, "PWD", cwd, free);
	}
	exit_status = ft_strdup("0");
	if (!exit_status)
		return (-1);
	dict_set(d_env, "?", exit_status, free);
	return (0);
}

t_dict	*init_d_env(char **env)
{
	int		size;
	t_dict	*d_env;

	size = 10;
	if (!env)
		return (NULL);
	while (env && env[size])
		size++;
	d_env = dict_create(size);
	if (!d_env)
		return (NULL);
	size = 0;
	while (env && env[size])
	{
		if (set_raw(env[size], &d_env) < 0)
			return (NULL);
		size++;
	}
	if (minimal_env(d_env) == -1)
	{
		dict_destroy(d_env, free);
		return (NULL);
	}
	return (d_env);
}
