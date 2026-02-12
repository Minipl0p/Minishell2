/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 09:56:35 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/11 16:50:05 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/Includes/libft.h"
#include "../../Includes/ast.h"
#include <stdio.h>
#include <unistd.h>

static int	ft_isnumarg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_ast_node *cmd, t_dict *d_env)
{
	int	exit_status;

	exit_status = 0;
	(void)d_env;
	if (!cmd)
		return (-1);
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (!cmd->argv[1])
		exit(0);
	if (ft_isnumarg(cmd->argv[1]))
	{
		if (cmd->argv[2])
		{
			ft_putendl_fd("Too many arguments", STDERR_FILENO);
			return (-1);
		}
		exit_status = ft_atoi(cmd->argv[1]);
		exit(exit_status);
	}
	else
	{
		ft_putendl_fd("Not a numeric arg", STDERR_FILENO);
		exit(2);
	}
}
