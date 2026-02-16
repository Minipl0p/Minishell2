/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 13:26:10 by pcaplat           #+#    #+#             */
/*   Updated: 2026/02/16 15:09:15 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "../../libft/Includes/ft_string.h"
#include "../../Includes/pipeline.h"

void	ft_print_error(int sh_error, char *msg, char *target)
{
	char	*error;

	if (sh_error)
		write(2, "Minishell: ", 11);
	if (target)
	{
		write(2, target, ft_strlen(target));
		write(2, ": ", 2);
	}
	if (msg)
		write(2, msg, ft_strlen(msg));
	else
	{
		error = strerror(errno);
		write(2, error, ft_strlen(error));
	}
	write(2, "\n", 1);
}

void	exit_path_error(t_ast_node *cmd, t_pipeline *data, int perm_error)
{
	char	*target;

	target = NULL;
	if (cmd->argv && cmd->argv[0])
		target = cmd->argv[0];
	if (perm_error == 0 && target)
		ft_print_error(0, "Command not found", target);
	else if (perm_error == 1)
		ft_print_error(1, NULL, target);
	free_child(data, NULL);
	exit(127);
}

