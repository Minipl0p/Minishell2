/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banner_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchazalm <pchazalm@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 09:49:01 by pchazalm          #+#    #+#             */
/*   Updated: 2026/02/17 09:51:25 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/builtin.h"
#include "../../Includes/banner.h"

int	ft_banner(t_ast_node *cmd, t_dict *d_env)
{
	(void)cmd;
	(void)d_env;
	print_banner();
	return (0);
}
