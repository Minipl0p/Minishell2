/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 19:28:41 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/31 19:29:09 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/expand.h"

static char	*remove_fctn(char *str, int pos)
{
	char	*new;

	if (!str)
		return (0);
	new = ft_calloc(sizeof(char), ft_strlen(str));
	if (!new)
		return (NULL);
	ft_strlcat(new, str, pos + 1);
	ft_strcat(new, str + pos + 1);
	free(str);
	return (new);
}

int	remove_quote_step(char **av)
{
	int		i;
	int		flag;

	flag = 0;
	while ((*av)[i])
	{
		if (flag == 0 && ((*av)[i] == '\'' || (*av)[i] == '"'))
		{
			flag += ((*av)[i] == '\'') + 2 * ((*av)[i] == '"');
			(*av) = remove_fctn((*av), i);
		}
		else if ((flag == 1 && (*av)[i] == '\'')
			|| (flag == 2 && (*av)[i] == '\"'))
		{
			flag += ((*av)[i] == '\'') + 2 * ((*av)[i] == '"');
			(*av) = remove_fctn((*av), i);
		}
		else
			i++;
		if (!*av)
			return (-1);
	}
	return (0);
}

int	remove_quote(char **av)
{
	int		j;

	j = 0;
	if (!av || !*av)
		return (0);
	while (av[j])
	{
		if (remove_quote_step(&(av[j])) == -1)
			return (-1);
		j++;
	}
	return (0);
}
