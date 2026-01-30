/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 15:20:01 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/30 23:30:13 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "ast.h"
# include <fcntl.h>
# include <stdio.h>

int	expand_flatten(t_list *cmds, t_dict *d_env);
int	expand_str(char **str, t_dict *d_env);

#endif
