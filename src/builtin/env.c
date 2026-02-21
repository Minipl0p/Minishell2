/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 10:07:48 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/21 12:23:30 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/builtin.h"
#include "../../Includes/errors.h"

int	ft_env(t_ast_node *cmd, t_dict *d_env)
{
	char	**env;
	char	**args;
	int		i;

	signal(SIGPIPE, SIG_IGN);
	args = cmd->argv;
	if (!d_env || !args || !*args || ft_strcmp(*args, "env"))
		return (1);
	if (args[1])
	{
		ft_print_error(1, "Too many arguments", "env");
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
