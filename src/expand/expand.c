/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:56:20 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/31 19:41:09 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/expand.h"
#include <stdio.h>

char	**manage_interpretor(char *argv, t_dict *d_env)
{
	char	*tmp;
	char	**new;

	tmp = expand_str(argv, d_env);
	if (!tmp)
		return (NULL);
	new = split_quoted(tmp);
	free(tmp);
	return (new);
}

char	**manage_wildcard(char *argv, t_dict *d_env)
{
	char	**new;
	char	*tmp;

	(void)d_env;
	tmp = expand_wildcard(argv);
	if (!tmp)
		return (NULL);
	new = split_quoted(tmp);
	free(tmp);
	return (new);
}

static int	manage(char **argv, t_dict *d_env, char **(*f)(char *, t_dict *))
{
	int		ret;
	int		i;
	char	**new;

	i = 0;
	while (argv[i])
	{
		new = f(argv[i], d_env);
		if (!new)
			return (-1);
		ret = insert_arr(argv, i, new);
		ft_free_arr((void **)new);
		if (ret == -1)
			return (-1);
		i++;
	}
	return (0);
}

static int	expand_argv(char **argv, t_dict *d_env)
{
	if (manage(argv, d_env, manage_interpretor) == -1)
		return (-1);
	if (manage(argv, d_env, manage_wildcard) == -1)
		return (-1);
	if (remove_quote(argv) == -1)
		return (-1);
	return (0);
}

int	expand_flatten(t_list *cmds, t_dict *d_env)
{
	int		err;
	t_list	*head;

	if (!cmds)
		return (0);
	head = cmds;
	err = expand_argv(((t_ast_node *)cmds->content)->argv, d_env);
	if (err == -1)
		return (-1);
	// redir other 
	// redir explore_heredocs
	// liste chaine de cmd !
	return (err);
}
