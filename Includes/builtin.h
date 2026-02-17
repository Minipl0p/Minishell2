/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 09:32:52 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/17 15:25:01 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../libft/Includes/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include "dict.h"
# include "signals.h"
# include "ast.h"

int		ft_export_no_args(t_ast_node *cmd, t_dict *d_env);
int		ft_cd(t_ast_node *cmd, t_dict *d_env);
int		ft_echo(t_ast_node *cmd, t_dict *d_env);
int		ft_exit(t_ast_node *cmd, t_dict *d_env);
int		ft_env(t_ast_node *cmd, t_dict *d_env);
int		ft_export(t_ast_node *cmd, t_dict *d_env);
int		ft_unset(t_ast_node *cmd, t_dict *d_env);
int		ft_pwd(t_ast_node *cmd, t_dict *d_env);
void	cat_append(char **p, char *content, char *eq, int len);
int		ft_banner(t_ast_node *cmd, t_dict *d_env);

#endif
