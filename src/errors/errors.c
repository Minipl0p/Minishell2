/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 13:26:10 by pcaplat           #+#    #+#             */
/*   Updated: 2026/02/06 13:43:25 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../libft/Includes/ft_string.h"
#include <errno.h>
#include <string.h>
#include <stdio.h>

int	ft_puterror(char *msg, char *target, int status)
{
	char	*error;

	write(2, "Minishell: ", 11);
	if (target)
		write(2, &target, ft_strlen(target));
	if (msg)
		write(2, &msg, ft_strlen(msg));
	else
	{
		error = strerror(errno);
		if (!error)
		{
			perror("Minishell: malloc");
			return (-1);
		}
		write(2, &error, ft_strlen(error));
	}
	write(2, "\n", 1);
	return (status);
}
