/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 00:13:38 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/21 12:06:06 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/builtin.h"
#include "../../Includes/errors.h"

static char	*get_old(t_dict *d_env)
{
	char	*old;
	char	*tmp;

	tmp = dict_get(d_env, "PWD");
	if (tmp)
		old = ft_strdup(tmp);
	else
		old = ft_strdup("");
	return (old);
}

static char	*get_dest(t_dict *env, char *arg)
{
	char	*home;
	char	*path;

	if (arg && ft_strncmp(arg, "~", 1) != 0)
		return (arg);
	home = dict_get(env, "HOME");
	if (!home)
	{
		ft_print_error(1, "$HOME is not set", "cd");
		return (NULL);
	}
	if (!arg || !ft_strcmp(arg, "~"))
		return (home);
	if (ft_strncmp(arg, "~/", 2) == 0)
	{
		path = ft_strjoin(home, arg + 1);
		return (path);
	}
	return (arg);
}

static void	update_pwd(t_dict *env, char *oldpwd)
{
	char	*curr;

	dict_set(env, "OLDPWD", oldpwd, free);
	curr = getcwd(NULL, 0);
	if (curr)
		dict_set(env, "PWD", curr, free);
}

int	ft_cd(t_ast_node *cmd, t_dict *d_env)
{
	char	*dest;
	char	*old;
	char	**args;

	signal(SIGPIPE, SIG_IGN);
	args = cmd->argv;
	if (args[1] && args[2])
	{
		ft_print_error(1, "Too many arguments", "cd");
		return (1);
	}
	old = get_old(d_env);
	if (!old)
		return (1);
	dest = get_dest(d_env, args[1]);
	if (!dest || chdir(dest) == -1)
	{
		if (dest)
			ft_print_error(1, "Cd failed", NULL);
		return (1);
	}
	update_pwd(d_env, old);
	return (0);
}
