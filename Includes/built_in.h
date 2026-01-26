/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 17:22:19 by pcaplat           #+#    #+#             */
/*   Updated: 2026/01/22 17:30:11 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H
# include "ast.h"

typedef enum e_built_in
{
	NOT,
	FAKE
}	t_built_in;

int	is_built_in(t_ast_node *cmd);

#endif
