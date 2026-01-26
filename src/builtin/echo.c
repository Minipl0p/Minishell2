/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 23:39:10 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/26 10:03:53 by miniplop         ###   ########.fr       */
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

int	echo(t_btree *ast, t_dict *d_env)
{
	int		i;
	int		j;
	int		no_nl;
	char	**cmd;

	cmd = ((t_ast_node *)ast->content)->argv;
	(void)d_env;
	if (ft_strcmp(cmd[0], "echo"))
		return (-1);
	j = 1;
	no_nl = 0;
	while (!ft_strncmp(cmd[j], "-n", 2))
	{
		i = 0;
		while (cmd[j][i] && cmd[j][i] == 'n')
			i++;
		if (cmd[j][i] != '\0')
			break ;
		no_nl = 1;
		j++;
	}
	print_args(cmd + j, no_nl);
	return (0);
}
