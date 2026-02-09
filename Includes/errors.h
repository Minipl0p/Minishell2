/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 16:01:16 by pcaplat           #+#    #+#             */
/*   Updated: 2026/02/09 10:37:47 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H
# include "pipeline.h"

int		ft_print_error(int sh_error, char *msg, char *target);
void	put_perm_error(t_pipeline *data, char *target, int i, int perm_error);

#endif
