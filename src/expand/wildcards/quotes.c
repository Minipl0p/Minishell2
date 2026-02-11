/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:04:33 by pcaplat           #+#    #+#             */
/*   Updated: 2026/02/11 16:16:26 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libft/Includes/libft.h"

static char	*remove_lst_fctn(char *str, int pos)
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

char	*does_remove(int *flag, char *str, int *i)
{
	if (*flag == 0 && (str[*i] == '\'' || str[*i] == '"'))
	{
		*flag += (str[*i] == '\'') + 2 * (str[*i] == '"');
		str = remove_lst_fctn(str, *i);
	}
	else if ((*flag == 1 && str[*i] == '\'')
		|| (*flag == 2 && str[*i] == '"'))
	{
		*flag = 0;
		str = remove_lst_fctn(str, *i);
	}
	else
		(*i)++;
	return (str);
}

void	remove_quotes_in_list(t_list *lst)
{
	char	*str;
	int		i;
	int		flag;

	while (lst)
	{
		str = (char *)lst->content;
		i = 0;
		flag = 0;
		while (str[i])
		{
			str = does_remove(&flag, str, &i);
			if (!str || !str[i])
				break ;
		}
		lst->content = str;
		lst = lst->next;
	}
}
