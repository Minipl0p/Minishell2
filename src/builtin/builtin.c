/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:58:17 by pcaplat           #+#    #+#             */
/*   Updated: 2026/01/29 16:12:20 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/Includes/ft_string.h"
#include "../../Includes/ast.h"

int	is_built_in(t_ast_node *cmd)
{
	if (!cmd)
		return (-1);
	if (!ft_strcmp(cmd->argv[0], "cd"))
		return (1);
	if (!ft_strcmp(cmd->argv[0], "echo"))
		return (2);
	if (!ft_strcmp(cmd->argv[0], "env"))
		return (3);
	if (!ft_strcmp(cmd->argv[0], "exit"))
		return (4);
	if (!ft_strcmp(cmd->argv[0], "export"))
		return (5);
	if (!ft_strcmp(cmd->argv[0], "pwd"))
		return (6);
	if (!ft_strcmp(cmd->argv[0], "unset"))
		return (7);
	return (0);
}
