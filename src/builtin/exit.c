/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 09:56:35 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/30 16:50:00 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/Includes/libft.h"
#include "../../Includes/ast.h"

int	ft_exit(t_ast_node *cmd, t_dict *d_env)
{
	int	exit_status;

	exit_status = 0;
	if (cmd && cmd->argv && cmd->argv[1])
		exit_status = ft_atoi(cmd->argv[1]);
	if (d_env)
		dict_destroy(d_env, free);
	ft_putendl_fd("exit", 1);
	exit(exit_status);
}
