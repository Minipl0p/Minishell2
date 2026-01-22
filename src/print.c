/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:01:18 by pcaplat           #+#    #+#             */
/*   Updated: 2026/01/22 16:40:33 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	log_cmd_lst(t_list *lst)
{
	t_list	*tmp;
	int		i;
	int		count;

	printf("=====CMD_LIST=====\n");
	tmp = lst;
	count = 1;
	while (tmp)
	{
		i = 0;
		printf("cmd : %d\n", count);
		while (((t_ast_node *)tmp->content)->argv[i])
			printf("%s ", ((t_ast_node *)tmp->content)->argv[i++]);
		printf("\n");
		tmp = tmp->next;
		count++;
	}
}
