/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 09:32:52 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/27 12:23:15 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

#include "../../libft/Includes/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include "dict.h"
#include "ast.h"

typedef enum	e_builtin
{
	CD,
	ECHO,
	B_ENV,
	EXPORT,
	UNSET,
	PWD
}	t_builtin;

int	ft_export_no_args(t_dict *d_env);
int	ft_cd(t_btree *ast, t_dict *d_env);
int	ft_echo(t_btree *ast, t_dict *d_env);
int	ft_env(t_btree *ast, t_dict *d_env);
int	ft_export(t_btree *ast, t_dict *d_env);
int	ft_unset(t_btree *ast, t_dict *d_env);
int	ft_pwd(t_btree *ast, t_dict *d_env);

#endif
