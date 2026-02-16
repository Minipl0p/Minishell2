/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 16:01:16 by pcaplat           #+#    #+#             */
/*   Updated: 2026/02/16 15:04:46 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H
# include "pipeline.h"

int		ft_print_error(int sh_error, char *msg, char *target);
void	exit_path_error(t_ast_node *cmd, t_pipeline *data, int perm_error);

#endif
