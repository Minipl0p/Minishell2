/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:21:07 by pcaplat           #+#    #+#             */
/*   Updated: 2026/02/04 15:59:25 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include "../../../libft/Includes/ft_list.h"
#include "../../../libft/Includes/ft_dict.h"
#include "../../../Includes/expand.h"

int	add_to_expand_list(t_list **e_lst, char *str)
{
	t_list *node;

	if (!str)
		return (-1);
	node = ft_lstnew((void *)str);
	if (!node)
		return (-1);
	if (!*e_lst)
		*e_lst = node;
	else
		ft_lstadd_back(e_lst, node);
	return (1);
}

static int	build_dir_lst(t_list **dir_lst)
{
	DIR				*curr_dir;
	struct dirent	*curr_file;
	char			*file_name;

	curr_dir = opendir(".");
	if (!curr_dir)
		return (-1);
	curr_file = readdir(curr_dir);
	while (curr_file)
	{
		file_name = ft_strdup(curr_file->d_name);
		if (add_to_expand_list(dir_lst, file_name) == -1)
		{
			closedir(curr_dir);
			return (-1);
		}
		curr_file = readdir(curr_dir);
	}
	closedir(curr_dir);
	return (0);
}

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

int	remove_lst_quote(char **av)
{
	int		i;
	int		flag;

	flag = 0;
	i = 0;
	while ((*av)[i])
	{
		if (flag == 0 && ((*av)[i] == '\'' || (*av)[i] == '"'))
		{
			flag += ((*av)[i] == '\'') + 2 * ((*av)[i] == '"');
			(*av) = remove_lst_fctn((*av), i);
		}
		else if ((flag == 1 && (*av)[i] == '\'')
			|| (flag == 2 && (*av)[i] == '\"'))
		{
			flag += ((*av)[i] == '\'') + 2 * ((*av)[i] == '"');
			(*av) = remove_lst_fctn((*av), i);
		}
		else
			i++;
		if (!*av)
			return (-1);
	}
	return (0);
}

static int	expand_wildcards(char *str, t_list **lst)
{
	t_list	*dir_lst;
	t_list	*head;
	char	*tmp;

	dir_lst = NULL;
	if (build_dir_lst(&dir_lst) == -1)
	{
		ft_lstclear(&dir_lst, free);
		return (-1);
	}
	trunc_start(&dir_lst, str);
	trunc_middle(&dir_lst, str);
	trunc_last(&dir_lst, str);
	head = dir_lst;
	while (head)
	{
		tmp = (char *)head->content;
		remove_lst_quote(&tmp);
		head = head->next;
	}
	if (!*lst)
		*lst = dir_lst;
	else
		ft_lstadd_back(lst, dir_lst);
	return (0);
}

static int	is_expandable(char *str)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (str[i])
	{
		if (flag == 0 && (str[i] == '\'' || str[i] == '"'))
			flag += (str[i] == '\'') + 2 * (str[i] == '"');
		else if (flag != 1 && str[i] == '*')
				return (1);
		else if ((flag == 1 && str[i] == '\'') || (flag = 2 && str[i] == '"'))
			flag -= (str[i] == '\'') + 2 * (str[i] == '"');
		else
			i++;
	}
	return (0);
}

int	e_wildcard_unquote(char *str, t_list **expand_lst)
{
	char	*new_str;

	if (!str)
		return (-1);
	if (!is_expandable(str))
	{
		new_str = ft_strdup(str);
		if (!new_str)
			return (-1);
		add_to_expand_list(expand_lst, new_str);
	}
	else
		expand_wildcards(str, expand_lst);
	return (1);
}
