/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchazalm <pchazalm@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 08:46:25 by pchazalm          #+#    #+#             */
/*   Updated: 2026/02/21 14:53:23 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/builtin.h"
#include "../../Includes/errors.h"

static int	is_valid_args(char *arg, int *ret)
{
	int	i;

	i = 0;
	while (arg && arg[i] && arg[i] != '+' && arg[i] != '='
		&& (arg[i] == '_' || ft_isalpha(arg[i])))
		i++;
	if (arg[i] == 0 || arg[i] == '+' || arg[i] == '=')
		return (1);
	ft_print_error(1, "Not a valid identifier", arg);
	*ret = 1;
	return (0);
}

static int	replace_export(char *arg, char *eq, t_dict *d_env)
{
	char	*key;
	char	*content;

	key = ft_strndup(arg, eq - arg);
	if (!key)
		return (-1);
	if (*(eq + 1))
		content = ft_strdup(eq + 1);
	else
		content = ft_strdup("");
	if (!content)
	{
		free(key);
		return (-1);
	}
	dict_set(d_env, key, content, free);
	free(key);
	return (0);
}

static int	cat_export(char *arg, char *plus, t_dict *d_env)
{
	char	*key;
	char	*content;

	key = ft_strndup(arg, plus - arg);
	if (!key)
		return (-1);
	content = dict_get(d_env, key);
	if (!content)
		content = ft_strdup(plus + 2);
	else
		content = ft_strjoin(content, plus + 2);
	if (!content)
	{
		free(key);
		return (-1);
	}
	dict_set(d_env, key, content, free);
	free(key);
	return (1);
}

static int	which_export(char *arg, t_dict *d_env)
{
	char	*eq;
	char	*key;
	int		ret;

	ret = 0;
	eq = ft_strchr(arg, '=');
	if (!eq)
	{
		if (dict_get(d_env, arg))
			return (0);
		key = ft_strdup(arg);
		if (!key)
			return (-1);
		dict_set(d_env, key, NULL, free);
	}
	else
	{
		if (*(eq - 1) == '+')
			ret = cat_export(arg, eq - 1, d_env);
		else
			ret = replace_export(arg, eq, d_env);
	}
	return (ret);
}

int	ft_export(t_ast_node *cmd, t_dict *d_env)
{
	int		i;
	char	**args;
	int		ret;

	signal(SIGPIPE, SIG_IGN);
	ret = 0;
	args = cmd->argv;
	if (!args[1])
		return (ft_export_no_args(cmd, d_env));
	else
	{
		i = 0;
		while (args[++i])
		{
			if (!is_valid_args(args[i], &ret))
				continue ;
			if (which_export(args[i], d_env) < 0)
				return (-1);
		}
	}
	return (ret);
}
