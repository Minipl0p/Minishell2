/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 13:26:10 by pcaplat           #+#    #+#             */
/*   Updated: 2026/02/09 10:37:13 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
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

void	put_perm_error(t_pipeline *data, char *target, int i, int perm_error)
{
	if ((i != data->cmd_count - 1 || data->out_fd != -1) && perm_error == 0)
		ft_print_error(0, "Command not found", target);
	else
		ft_print_error(1, NULL, NULL);
}
