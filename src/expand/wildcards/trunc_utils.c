/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trunc_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 20:16:20 by pcaplat           #+#    #+#             */
/*   Updated: 2026/02/05 17:55:55 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libft/Includes/libft.h"

static void	ft_strncat(char *dest, char *src, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest && dest[j])
		j++;
	while (src[i] && i < len)
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	return ;
}

char	*ft_strcpy_sep_skip(char *str, char sep, int len)
{
	int		flag;
	int		i;
	char	*new_str;

	flag = 0;
	i = 0;
	new_str = ft_calloc(sizeof(char), len + 1);
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (flag == 0 && (str[i] == '\'' || str[i] == '"'))
			flag += (str[i] == '\'') + 2 * (str[i] == '"');
		else if (!str[i] || (flag == 0 && str[i] == sep))
			return (new_str);
		else if ((flag == 2 && str[i] == '"') || (flag == 1 && str[i] == '\''))
			flag -= (str[i] == '\'') + 2 * (str[i] == '"');
		else
			ft_strncat(new_str, &str[i], 1);
		i++;
	}
	return (new_str);
}

int	ft_strlen_sep_skip(char *str, char sep)
{
	int	flag;
	int	len;
	int	i;

	len = 0;
	flag = 0;
	i = 0;
	while (str[i])
	{
		if (flag == 0 && (str[i] == '\'' || str[i] == '"'))
			flag += (str[i] == '\'') + 2 * (str[i] == '"');
		else if (!str[i] || (flag == 0 && str[i] == sep))
			return (len);
		else if ((flag == 2 && str[i] == '"') || (flag == 1 && str[i] == '\''))
			flag -= (str[i] == '\'') + 2 * (str[i] == '"');
		else
			len++;
		i++;
	}
	return (len);
}

void	remove_lst(t_list **dir_lst, t_list *to_remove)
{
	t_list	*curr;
	t_list	*prev;
	t_list	*next;

	if (!dir_lst || !*dir_lst)
		return ;
	prev = *dir_lst;
	curr = *dir_lst;
	if (curr == to_remove)
	{
		*dir_lst = curr->next;
		ft_lstdelone(curr, free);
		return ;
	}
	while (curr && curr != to_remove)
	{
		prev = curr;
		curr = curr->next;
		next = curr->next;
	}
	prev->next = next;
	ft_lstdelone(curr, free);
}
