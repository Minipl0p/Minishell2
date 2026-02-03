/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trunc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 14:39:05 by pcaplat           #+#    #+#             */
/*   Updated: 2026/02/03 17:55:39 by pcaplat          ###   ########.fr       */
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
	t_list	*head;
	t_list	*next;
	int		i;

	head = *dir_lst;
	next = NULL;
	if (!dir_lst || !*dir_lst)
		return ;
	i = 0;
	while (i < count)
	{
		head = head->next;
		i++;
	}
	if (count == 0)
	{
		head = head->next;
		free((*dir_lst)->content);
		free(*dir_lst);
		*dir_lst = head;
		return ;
	}
	next = head->next->next;
	free(head->next->content);
	free(head->next);
	head->next = next;
}

int	trunc_start(t_list **dir_lst, char *arg)
{
	int		len;
	char	*start;
	t_list	*head;
	int		count;
	int		size;

	len = ft_strlen_sep_skip(arg, '*');
	start = ft_strcpy_sep_skip(arg, '*', len);
	if (!start)
		return (-1);
	head = *dir_lst;
	count = 0;
	size = ft_lstsize(*dir_lst);
	while (count != size)
	{
		if (ft_strncmp((*dir_lst)->content, start, len))
			remove_lst(dir_lst, count);
		count++;
		size = ft_lstsize(*dir_lst);
	}
	return (0);
}

char	*skip_to_next_star(char *arg)
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
		else
			i++;
	}
	return (NULL);
}

t_list	*create_word_lst(char *arg)
{
	t_list	*word_lst;
	char	*tmp;
	char	*word;
	int		i;
	int		len;

	word_lst = NULL;
	i = 0;
	tmp = skip_to_next_star(arg);
	while (tmp)
	{
		if (!(tmp + 1))
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

int	is_correct_name(t_list *head, t_list *word_lst)
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

int	trunc_middle(t_list **dir_lst, char *arg)
{
	t_list	*word_lst;
	t_list	*head;
	int		count;

	word_lst = create_word_lst(arg);
	if (!word_lst)
		return (-1);
	head = *dir_lst;
	count = 0;
	while (head)
	{
		if (is_correct_name(head, word_lst) < 0)
			remove_lst(dir_lst, count);
		count++;
		head = head->next;
	}
	return (0);
}

int	is_correct_char(t_list *head, int i, char c)
{
	int	len;

	len = ft_strlen(head->content);
	if (((char *)head->content)[len - i] == c)
		return (1);
	return (0);
}

void	trunc_last(t_list **dir_lst, char *arg)
{
	t_list	*head;
	int		i;
	int		count;
	int		len;
	int		flag;

	i = 0;
	flag = 0;
	len = ft_strlen(arg);
	head = *dir_lst;
	while (arg[len - ++i] && !(arg[i] == '*' && flag == 0))
	{
		if (flag == 0 && (arg[len - i] == '\'' || arg[len - i] == '"'))
			flag += (arg[len - i] == '\'') + 2 * (arg[len - i] == '"');
		count = 0;
		while (head)
		{
			if (is_correct_char(head, i, arg[len - i] == 0))
				remove_lst(dir_lst, count);
			count++;
			head = head->next;
		}
		if ((flag == 2 && arg[len - i] == '"') || (flag == 1 && arg[len - i] == '\''))
			flag -= (arg[len - i] == '\'') + 2 * (arg[len - i] == '"');
	}
}
