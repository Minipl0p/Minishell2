/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 09:42:18 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/30 12:48:40 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/builtin.h"

int	ft_unset(t_ast_node *cmd, t_dict *d_env)
{
	int		i;
	char	**args;

	args = cmd->argv;
	if (!args || !d_env || !args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		if (args[i][0] && (args[i][0] == '_' || ft_isalpha(args[i][0])))
			dict_remove(d_env, args[i], free);
		i++;
	}
	return (0);
}
