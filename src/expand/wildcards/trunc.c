/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trunc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 14:39:05 by pcaplat           #+#    #+#             */
/*   Updated: 2026/02/02 17:03:39 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/expand.h"

static char	*ft_strcpy_sep_skip(char *str, char sep, int len)
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
		if (!str[i] || (flag == 0 && str[i] == sep))
			return (new_str);
		if ((flag == 2 && str[i] == '"') || (flag == 1 && str[i] == '\''))
			flag -= (str[i] == '\'') + 2 * (str[i] == '"');
		else
			ft_strlcat(new_str, &str[i], 2);
		i++;
	}
	return (new_str);
}

static int	ft_strlen_sep_skip(char *str, char sep)
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
		if (!str[i] || (flag == 0 && str[i] == sep))
			return (len);
		if ((flag == 2 && str[i] == '"') || (flag == 1 && str[i] == '\''))
			flag -= (str[i] == '\'') + 2 * (str[i] == '"');
		else
			len++;
		i++;
	}
	return (len);
}

static void	remove_lst(t_list **dir_lst, int count)
{
	t_list	*prev;
	t_list	*next;
	int		i;

	prev = NULL;
	next = NULL;
	if (!dir_lst || !*dir_lst)
		return ;
	i = 0;
	while (i < count)
	{
		(*dir_lst) = (*dir_lst)->next;
		i++;
	}
	next = (*dir_lst)->next->next;
	free((*dir_lst)->next->content);
	free((*dir_lst)->next);
	(*dir_lst)->next = next;
}

int	trunc_start(t_list **dir_lst, char *arg)
{
	int		len;
	char	*start;
	t_list	*head;
	int		count;

	len = ft_strlen_sep_skip(arg, '*');
	start = ft_strcpy_sep_skip(arg, '*', len);
	if (!start)
		return (-1);
	head = *dir_lst;
	count = 0;
	while (head)
	{
		if (ft_strncmp(head->content, start, len))
			remove_lst(dir_lst, count);
		count++;
	}
	return (0);
}

char	*skip_to_next_star(char *arg)
{

}

int	trunc_middle(t_list **dir_lst, char *arg)
{
	t_list	*word_lst;
	t_list	*head;
	char	*word;
	char	*word_middle;
	int		len;

	word_lst = NULL;
	word = skip_to_next_star(arg);
	len = ft_strlen_sep_skip(word + 1, '*');
	word_middle = ft_strcpy_sep_skip(word + 1, '*', len);
	if (!word_middle)
		return (-1);
	add_to_expand_list(&word_lst, word_middle);
	while (word_middle)
	{
		word = skip_to_next_star(word_middle);
		len = ft_strlen_sep_skip(word + 1, '*');
		word_middle = ft_strcpy_sep_skip(word + 1, '*', len);
		if (!is_last_star(word_middle))
			add_to_expand_list(&word_lst, word_middle);
	}
}
