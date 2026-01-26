/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 09:56:35 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/26 10:15:08 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/Includes/libft.h"
#include "../../Includes/ast.h"

int	ft_exit(t_btree *ast, t_dict *d_env)
{
	dict_destroy(d_env, free);
	ast_destroy(ast);
	exit (0);
}
