/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 14:41:16 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/20 16:28:05 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/expand.h"
#include "../../Includes/errors.h"

int	process_expand(char *str, t_list **final_list, t_dict *d_env)
{
	char	*step1_vars;
	char	**step2_split;
	int		i;

	step1_vars = expand_str_vars(str, d_env);
	if (!step1_vars)
		return (-1);
	step2_split = split_words_nquoted(step1_vars, ' ');
	free(step1_vars);
	if (!step2_split)
		return (-1);
	i = 0;
	while (step2_split[i])
	{
		if (e_wildcard_unquote(step2_split[i], final_list) == -1)
		{
			ft_free_arr((void **)step2_split);
			return (-1);
		}
		i++;
	}
	ft_free_arr((void **)step2_split);
	return (0);
}

static char	**lst_to_arr(t_list *lst)
{
	char	**arr;
	t_list	*head;
	int		size;

	arr = ft_calloc(ft_lstsize(lst) + 1, sizeof(char *));
	if (arr)
	{
		size = 0;
		head = lst;
		while (head)
		{
			arr[size] = ft_strdup(((char *)head->content));
			if (!arr[size])
			{
				ft_free_arr((void **)arr);
				break ;
			}
			head = head->next;
			size++;
		}
		ft_lstclear(&lst, free);
		return (arr);
	}
	ft_lstclear(&lst, free);
	return (NULL);
}

int	expand_argv_array(char ***argv_ptr, t_dict *env)
{
	char	**old_argv;
	t_list	*lst_res;
	int		i;

	old_argv = *argv_ptr;
	lst_res = NULL;
	i = 0;
	while (old_argv[i])
	{
		if (process_expand(old_argv[i], &lst_res, env) == -1)
		{
			ft_lstclear(&lst_res, free);
			return (-1);
		}
		i++;
	}
	ft_free_arr((void **)old_argv);
	remove_quotes_in_list(lst_res);
	*argv_ptr = lst_to_arr(lst_res);
	if (!*argv_ptr)
		ft_print_error(1, NULL, "malloc");
	return (0);
}
