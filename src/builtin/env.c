/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 10:07:48 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/26 10:04:14 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/builtin.h"

int	ft_env(t_btree *ast, t_dict *d_env)
{
	char	**env;
	int		i;
	char	**args;

	args = ((t_ast_node *)ast->content)->argv;
	if (!d_env || !args || !*args)
		return (1);
	if (ft_strcmp(*args, "env"))
		return (1);
	if (args[1])
	{
		ft_putstr_fd("minishell: env: too many arguments\n", 2);
		return (2);
	}
	env = dict_to_env(d_env);
	if (!env)
		return (1);
	i = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
				ft_putendl_fd(env[i++], STDOUT_FILENO);
	}
	ft_free_arr((void **)env);
	return (0);
}
