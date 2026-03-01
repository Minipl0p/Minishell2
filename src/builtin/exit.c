/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 09:56:35 by miniplop          #+#    #+#             */
/*   Updated: 2026/03/01 00:00:00 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/builtin.h"
#include "../../Includes/errors.h"

static int	ft_isnumarg(char *arg)
{
	int			i;
	long long	v;
	int			sign;

	if (!arg || !*arg)
		return (0);
	i = 0;
	sign = 1;
	if (arg[i] == '-' || arg[i] == '+')
		if (arg[i++] == '-')
			sign = -1;
	if (!arg[i])
		return (0);
	v = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		if (v > 922337203685477580 || (v == 922337203685477580
				&& (arg[i] - '0') > (7 + (sign < 0))))
			return (0);
		v = v * 10 + (arg[i++] - '0');
	}
	return (1);
}

static int	ft_exit_value(char *s)
{
	long long	v;

	v = ft_atol(s);
	v = (v % 256 + 256) % 256;
	return ((int)v);
}

int	ft_exit_forked(t_ast_node *cmd, t_dict *d_env)
{
	int	exit_status;

	signal(SIGPIPE, SIG_IGN);
	if (!cmd->argv[1])
	{
		exit_status = ft_atoi(dict_get(d_env, "?"));
		return (exit_status);
	}
	if (!ft_isnumarg(cmd->argv[1]))
	{
		ft_print_error(1, "Not a numeric arg", "exit");
		return (2);
	}
	if (cmd->argv[2])
	{
		ft_print_error(1, "Too many arguments", "exit");
		return (1);
	}
	exit_status = ft_exit_value(cmd->argv[1]);
	return (exit_status);
}

int	ft_exit(t_ast_node *cmd, t_dict *d_env)
{
	int	exit_status;

	signal(SIGPIPE, SIG_IGN);
	ft_putendl_fd("exit", STDERR_FILENO);
	if (!cmd->argv[1])
	{
		exit_status = ft_atoi(dict_get(d_env, "?"));
		dict_destroy(d_env, free);
		exit(exit_status);
	}
	if (!ft_isnumarg(cmd->argv[1]))
	{
		ft_print_error(1, "Not a numeric arg", "exit");
		return (2);
	}
	if (cmd->argv[2])
	{
		ft_print_error(1, "Too many arguments", "exit");
		return (1);
	}
	dict_destroy(d_env, free);
	exit_status = ft_exit_value(cmd->argv[1]);
	exit(exit_status);
}
