/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 17:24:27 by pcaplat           #+#    #+#             */
/*   Updated: 2026/01/22 17:36:35 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	fake(void)
{
	write(1, "Jack black is comming\n", 22);
}

int	is_built_in(t_ast_node *cmd)
{
	if (strcmp(cmd->argv[0], "fake") == 0)
		return (1);
	return (0);
}
