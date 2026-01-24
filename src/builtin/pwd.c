/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 23:50:08 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/24 23:59:23 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/includes/libft.h"
#include <stdlib.h>
#include <unistd.h>

int	pwd(char **args)
{
	char	*path;
	char	*dir;

	if (!args || args[1] || ft_strcmp(args[0], "pwd"))
		return (1);
	path = getcwd(NULL, 0);
	if (!path)
	{
		ft_putendl_fd("Minishell : pwd failed", STDERR_FILENO);
		return (NULL);
	}
	ft_putendl_fd(path, STDOUT_FILENO);
	free(path);
	return (0);
}
