/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 14:52:10 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/26 09:52:40 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/builtin.h"

static void	print_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(arr[i], STDOUT_FILENO);
		i++;
	}
	return ;
}

int	ft_export_no_args(t_dict *d_env)
{
	char	**exp;
	char	*tmp;
	int		i;
	int		j;

	exp = dict_to_env(d_env, EXP);
	if (!exp)
		return (1);
	j = 0;
	while (j < d_env->count - 1)
	{
		i = -1;
		while (++i < d_env->count - 1)
		{
			if (ft_strcmp(exp[i], exp[i + 1]) > 0)
			{
				tmp = exp[i];
				exp[i] = exp[i + 1];
				exp[i + 1] = tmp;
			}
		}
		j++;
	}
	print_arr(exp);
	return (0);
}
