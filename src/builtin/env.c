/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 10:07:48 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/30 16:49:15 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/builtin.h"

int	ft_env(t_ast_node *cmd, t_dict *d_env)
{
	char	**env;
	int		i;
	char	**args;

	args = cmd->argv;
	if (!d_env || !args || !*args)
		return (1);
	if (ft_strcmp(*args, "env"))
		return (1);
	if (args[1])
	{
		ft_putstr_fd("minishell: env: too many arguments\n", 2);
		return (2);
	}
	env = dict_to_env(d_env, ENV);
	if (!env)
		return (1);
	i = -1;
	while (env[++i])
	{
		if (ft_strchr(env[i], '='))
			ft_putendl_fd(env[i], STDOUT_FILENO);
	}
	ft_free_arr((void **)env);
	return (0);
}
