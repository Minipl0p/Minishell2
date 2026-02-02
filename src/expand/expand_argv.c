/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 14:41:16 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/02 11:15:39 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/expand.h"

int	process_expand(char *str, t_list **final_list, t_dict *d_env)
{
	char	*step1_vars;
	char	**step2_split;
	t_list	*wildcard_list;
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
		if (expand_wildcard_and_unquote(step2_split[i], final_list) == -1)
		{
			ft_free_arr((void **)step2_split);
			return (-1);
		}
		i++;
	}
	ft_free_arr((void **)step2_split);
	return (0);
}

// ATTENTION la conversion list to char **, il ne faudrais pas free le content de la lst si on a pas strdup ou free si on strdup
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
	*argv_ptr = lst_to_arr(lst_res);
	ft_lstclear(&lst_res, free);
	return (0);
}
