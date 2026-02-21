/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 23:50:08 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/21 12:13:45 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/builtin.h"
#include "../../Includes/errors.h"
#include <unistd.h>

int	ft_pwd(t_ast_node *cmd, t_dict *d_env)
{
	char	*path;
	char	**args;

	signal(SIGPIPE, SIG_IGN);
	args = cmd->argv;
	(void)d_env;
	if (!args || args[1] || ft_strcmp(args[0], "pwd"))
		return (1);
	path = getcwd(NULL, 0);
	if (!path)
	{
		ft_print_error(1, "Pwd failed", NULL);
		return (-1);
	}
	ft_putendl_fd(path, STDOUT_FILENO);
	free(path);
	return (0);
}
