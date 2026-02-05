/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trunc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 21:21:46 by pcaplat           #+#    #+#             */
/*   Updated: 2026/02/05 11:35:02 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/expand.h"
#include "../../../libft/Includes/ft_list.h"

int	trunc_start(t_list **dir_lst, char *arg)
{
	int		len;
	char	*start;
	t_list	*head;
	t_list	*to_del;

	len = ft_strlen_sep_skip(arg, '*');
	start = ft_strcpy_sep_skip(arg, '*', len);
	if (!start)
		return (-1);
	head = *dir_lst;
	while (head)
	{
		if (ft_strncmp(head->content, start, len))
		{
			to_del = head;
			head = head->next;
			remove_lst(dir_lst, to_del);
		}
		else
			head = head->next;
	}
	return (0);
}

static void	trunc_last_remove(t_list **dir_lst, char c, int i)
{
	t_list	*head;
	t_list	*to_del;
	int		len;

	head = *dir_lst;
	while (head)
	{
		len = ft_strlen(head->content);
		if (((char *)head->content)[len - i] != c)
		{
			to_del = head;
			head = head->next;
			remove_lst(dir_lst, to_del);
		}
		else
			head = head->next;
	}
}

void	trunc_last(t_list **dir_lst, char *arg)
{
	int		i;
	int		len;
	int		flag;

	i = 1;
	flag = 0;
	len = ft_strlen(arg);
	while (arg[len - i] && !(arg[len - i] == '*' && flag == 0))
	{
		if (flag == 0 && (arg[len - i] == '\'' || arg[len - i] == '"'))
			flag += (arg[len - i] == '\'') + 2 * (arg[len - i] == '"');
		trunc_last_remove(dir_lst, arg[len - i], i);
		if ((flag == 2 && arg[len - i] == '"') || (flag == 1 && arg[len - i] == '\''))
			flag -= (arg[len - i] == '\'') + 2 * (arg[len - i] == '"');
		i++;
	}
}
