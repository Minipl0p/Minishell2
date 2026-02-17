/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 09:56:35 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/17 16:26:14 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/builtin.h"

static int	is_overflow(char *arg)
{
	int		i;
	long	l;
	int		sign;

	sign = 1;
	i = 0;
	if (!arg || !*arg)
		return (1);
	if (arg[0] == '-' | arg[0] == '+')
	{
		if (arg[0] == '-')
			sign = -1;
		i++;
	}
	l = 0;
	while (arg[i])
	{
		l = l * 10 + (arg[i] - 0);
		if ((sign > 0 && l > 2147483647) || (sign < 0 && l < -2147483648))
			return (1);
		i++;
	}
	return (0);
}

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
	if (is_overflow(arg) == 1)
		return (0);
	return (1);
}

int	ft_exit(t_ast_node *cmd, t_dict *d_env)
{
	int	exit_status;

	signal(SIGPIPE, SIG_IGN);
	exit_status = 0;
	(void)d_env;
	if (!cmd)
		return (-1);
	ft_putendl_fd("exit", STDERR_FILENO);
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
