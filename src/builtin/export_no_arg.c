/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 14:52:10 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/01 13:11:50 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/builtin.h"

static void	print_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr || !*arr)
		return ;
	while (arr[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(arr[i], STDOUT_FILENO);
		i++;
	}
	return ;
}

static char	**sort_env(t_dict *d_env)
{
	char	**exp;
	int		i;
	size_t	j;
	char	*tmp;

	exp = dict_to_env(d_env, EXP);
	if (!exp)
		return (NULL);
	j = -1;
	while (++j < d_env->count - 1)
	{
		i = -1;
		while (++i < (int)d_env->count - 1)
		{
			if (exp[i + 1] && ft_strcmp(exp[i], exp[i + 1]) > 0)
			{
				tmp = exp[i];
				exp[i] = exp[i + 1];
				exp[i + 1] = tmp;
			}
		}
	}
	return (exp);
}

int	ft_export_no_args(t_ast_node *cmd, t_dict *d_env)
{
	char	**exp;

	(void)cmd;
	exp = sort_env(d_env);
	print_arr(exp);
	ft_free_arr((void **)exp);
	return (0);
}
