/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trunc_middle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:58:35 by pcaplat           #+#    #+#             */
/*   Updated: 2026/02/11 15:33:45 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/expand.h"
#include "../../../libft/Includes/ft_list.h"

static int	is_correct_name(t_list *head, t_list *word_lst)
{
	t_list	*head_w;
	char	*tmp;

	head_w = word_lst;
	tmp = (char *)head->content;
	while (head_w)
	{
		tmp = ft_strnstr(tmp, head_w->content, ft_strlen(tmp));
		if (!tmp)
			return (-1);
		head_w = head_w->next;
	}
	return (0);
}

static char	*skip_to_next_star(char *arg)
{
	int		flag;
	int		i;

	flag = 0;
	i = 0;
	while (arg[i])
	{
		if (flag == 0 && (arg[i] == '\'' || arg[i] == '"'))
			flag += (arg[i] == '\'') + 2 * (arg[i] == '"');
		if (!arg[i] || (flag == 0 && arg[i] == '*'))
			return (&arg[i]);
		if ((flag == 2 && arg[i] == '"') || (flag == 1 && arg[i] == '\''))
			flag -= (arg[i] == '\'') + 2 * (arg[i] == '"');
		i++;
	}
	return (NULL);
}

static t_list	*create_word_lst(char *arg)
{
	t_list	*word_lst;
	char	*tmp;
	char	*word;
	int		len;

	word_lst = NULL;
	tmp = skip_to_next_star(arg);
	while (tmp)
	{
		if (!(*(tmp + 1)))
			break ;
		len = ft_strlen_sep_skip(tmp + 1, '*');
		word = ft_strcpy_sep_skip(tmp + 1, '*', len);
		if (add_to_expand_list(&word_lst, word) < 0)
		{
			ft_lstclear(&word_lst, free);
			return (NULL);
		}
		tmp = skip_to_next_star(tmp + 1);
	}
	return (word_lst);
}

int	trunc_middle(t_list **dir_lst, char *arg)
{
	t_list	*word_lst;
	t_list	*head;
	t_list	*to_del;

	word_lst = create_word_lst(arg);
	if (!word_lst)
		return (-1);
	head = *dir_lst;
	while (head)
	{
		if (is_correct_name(head, word_lst) < 0)
		{
			to_del = head;
			head = head->next;
			remove_lst(dir_lst, to_del);
		}
		else
			head = head->next;
	}
	ft_lstclear(&word_lst, free); 
	return (0);
}
