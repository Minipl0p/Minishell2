/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 10:34:48 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/30 14:03:19 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/builtin.h"

static char	**parse_no_eq(char *arg)
{
	char	**p;

	p = ft_calloc(sizeof(char *), 2);
	if (!p)
		return (NULL);
	p[0] = ft_strdup(arg);
	if (!(p[0]))
	{
		free(p);
		return (NULL);
	}
	return (p);
}

static char	**parse_replace(char *arg, char *eq)
{
	char	**p;

	p = ft_calloc(sizeof(char *), 3);
	if (!p)
		return (NULL);
	p[0] = ft_strndup(arg, eq - arg);
	if (!(p[0]))
	{
		free(p);
		return (NULL);
	}
	p[1] = ft_strdup(eq + 1);
	if (!(p[1]))
	{
		ft_free_arr((void **)p);
		return (NULL);
	}
	return (p);
}

static char	**parse_append(char *arg, char *eq, t_dict *d)
{
	char	**p;
	char	*content;

	p = ft_calloc(sizeof(char *), 3);
	if (!p)
		return (NULL);
	p[0] = ft_strndup(arg, eq - 1 - arg);
	if (!(p[0]))
	{
		free(p);
		return (NULL);
	}
	content = dict_get(d, p[0]);
	p[1] = ft_calloc(sizeof(char), ft_strlen(content) + ft_strlen(eq) + 1);
	if (!p[1])
	{
		ft_free_arr((void **)p);
		return (NULL);
	}
	p[1] = ft_strcat(p[1], dict_get(d, p[0]));
	p[1] = ft_strcat(p[1], eq + 1);
	return (p);
}

int	ft_export(t_ast_node *cmd, t_dict *d_env)
{
	int		ret;
	int		i;
	char	**parsed;
	char	*eq;
	char	**args;

	args = cmd->argv;
	if (!args[1])
		return (ft_export_no_args(d_env));
	else
	{
		i = 0;
		while (args[++i])
		{
			eq = ft_strchr(args[i], '=');
			if (eq && *(eq - 1) == '+')
				parsed = parse_append(args[i], eq, d_env);
			else if (eq)
				parsed = parse_replace(args[i], eq);
			else
				parsed = parse_no_eq(args[i]);
			if (parsed)
				ret = dict_set(d_env, parsed[0], parsed[1], free);
			free(parsed[0]);
			free(parsed);
		}
	}
	return (ret);
}
