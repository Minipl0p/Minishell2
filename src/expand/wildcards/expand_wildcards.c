/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:21:07 by pcaplat           #+#    #+#             */
/*   Updated: 2026/02/02 17:03:50 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include "../../../libft/Includes/ft_list.h"
#include "../../../libft/Includes/ft_dict.h"

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
	t_list			*node;
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
	return (0);
}

static int	expand_wildcards(char *str, int i, t_dict *d_env, t_list **lst)
{
	t_list	*dir_lst;

	dir_lst = NULL;
	if (build_dir_lst(&dir_lst) == -1)
	{
		ft_lstclear(&dir_lst, free);
		return (-1);
	}
	trunc_start();
	trunc_middle();
	trunc_end();

	lst_remove_quote(dir_lst);
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

int	expand_wildcard_and_unquote(char *str, t_list **expand_lst, t_dict *d_env)
{
	if (!str)
		return (-1);
	if (!is_expandable(str))
		add_to_lst(expand_lst, str);
	else
		expand_wildcard(str, d_env, expand_lst);
	return (1);
}

//opendir(path)
