/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:01:18 by pcaplat           #+#    #+#             */
/*   Updated: 2026/01/22 19:11:10 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	log_cmd_lst(t_list *lst)
{
	t_list	*tmp;
	int		i;

	printf("=====CMD_LIST=====\n");
	tmp = lst;
	while (tmp)
	{
		i = 0;
		while (((t_ast_node *)tmp->content)->argv[i])
			printf("%s ", ((t_ast_node *)tmp->content)->argv[i++]);
		printf("\n");
		if (((t_ast_node *)tmp->content)->redirs)
			printf("target : %s\n", ((t_ast_node *)tmp->content)->redirs->target);
		tmp = tmp->next;
	}
}
