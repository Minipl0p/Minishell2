/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 16:01:16 by pcaplat           #+#    #+#             */
/*   Updated: 2026/02/16 17:02:25 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H
# include "pipeline.h"

void	ft_print_error(int sh_error, char *msg, char *target);
void	exit_path_error(t_ast_node *cmd, t_pipeline *data, int perm_error);
int		check_start_token(t_token *head, t_token *token_lst);
void	check_end_token(t_btree *ast, t_token *head);

#endif
