/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 00:13:38 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/25 10:04:49 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/Includes/libft.h"
#include <unistd.h>
#include <stdlib.h>

static void	free_cd_res(char *old, char *dest, int flags)
{
	if (flags & 1)
		free(old);
	if (flags & 2)
		free(dest);
}

static char	*get_old(t_dict *d_env, unsigned char *flags)
{
	char	*old;

	old = dict_get(d_env, "PWD");
	if (!old)
	{
		old = getcwd(NULL, 0);
		if (old)
			*flags = *flags | 1;
	}
	return (old);
}

static char	*get_dest(t_dict *env, char *arg, unsigned char *flags)
{
	char	*home;
	char	*path;

	if (arg && ft_strncmp(arg, "~", 1) != 0)
		return (arg);
	home = dict_get(env, "HOME");
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (NULL);
	}
	if (!arg || !ft_strcmp(arg, "~"))
		return (home);
	if (ft_strncmp(arg, "~/", 2) == 0)
	{
		path = ft_strjoin(home, arg + 1);
		if (path)
			*flags = *flags | 2;
		return (path);
	}
	return (arg);
}

static void	update_pwd(t_dict *env, char *oldpwd)
{
	char	*curr;

	dict_set(env, "OLDPWD", oldpwd);
	curr = getcwd(NULL, 0);
	if (curr)
	{
		dict_set(env, "PWD", curr);
		free(curr);
	}
}

int	cd(char **args, t_dict *d_env)
{
	char			*dest;
	char			*old;
	unsigned char	flags;

	if (args[1] && args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	flags = 0;
	old = get_old(d_env, &flags);
	if (!old)
		return (1);
	dest = get_dest(d_env, args[1], &flags);
	if (!dest || chdir(dest) == -1)
	{
		if (dest)
			ft_putendl_fd("minishell: cd failed", STDOUT_FILENO);
		free_cd_res(old, dest, flags);
		return (1);
	}
	update_pwd(d_env, old);
	free_cd_res(old, dest, flags);
	return (0);
}
