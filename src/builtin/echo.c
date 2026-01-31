/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 23:39:10 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/30 23:55:45 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/builtin.h"

void	print_args(char **args, int no_nl)
{
	int	i;

	if (!args || !*args)
		return ;
	i = 0;
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		i++;
		if (args[i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (no_nl == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

int	ft_echo(t_ast_node *cmd, t_dict *d_env)
{
	int		i;
	int		j;
	int		no_nl;
	char	**cmds;

	cmds = cmd->argv;
	(void)d_env;
	if (ft_strcmp(cmds[0], "echo") || !cmds[1])
		return (-1);
	j = 1;
	no_nl = 0;
	while (!ft_strncmp(cmds[j], "-n", 2))
	{
		i = 1;
		while (cmds[j][i] && cmds[j][i] == 'n')
			i++;
		if (cmds[j][i] != '\0')
			break ;
		no_nl = 1;
		j++;
	}
	print_args(cmds + j, no_nl);
	return (0);
}
