/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 09:56:35 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/21 14:52:32 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/builtin.h"
#include "../../Includes/errors.h"

static int	overflow_process(int sign, long int l, long int ol, char c)
{
	if (sign > 0 && l < ol)
		return (1);
	if (sign < 0 && l == 922337203685477580 && c - '0' > 8)
		return (1);
	return (0);
}

static int	is_overflow(char *arg)
{
	int			i;
	long long	l;
	long long	ol;
	int			sign;

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
		ol = l;
		l = l * 10 + (arg[i] - '0');
		if (overflow_process(sign, l, ol, arg[i + 1]) == 1)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_isnumarg(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
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

int	ft_exit_forked(t_ast_node *cmd, t_dict *d_env)
{
	static int	exit_status = 0;

	signal(SIGPIPE, SIG_IGN);
	(void)d_env;
	if (!cmd)
		return (-1);
	if (!cmd->argv[1])
		return (0);
	if (ft_isnumarg(cmd->argv[1]))
	{
		if (cmd->argv[2])
		{
			ft_print_error(1, "Too many arguments", "exit");
			return (-1);
		}
		exit_status = ft_atoi(cmd->argv[1]);
		exit_status = (exit_status % 256 + 256) % 256;
		return (exit_status);
	}
	else
	{
		ft_print_error(1, "Not a numeric arg", "exit");
		return (2);
	}
}

int	ft_exit(t_ast_node *cmd, t_dict *d_env)
{
	static int	exit_status = 0;

	signal(SIGPIPE, SIG_IGN);
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
			ft_print_error(1, "Too many arguments", "exit");
			return (1);
		}
		exit_status = ft_atol(cmd->argv[1]);
		exit_status = (exit_status % 256 + 256) % 256;
		exit(exit_status);
	}
	else
	{
		ft_print_error(1, "Not a numeric arg", "exit");
		exit(2);
	}
}
