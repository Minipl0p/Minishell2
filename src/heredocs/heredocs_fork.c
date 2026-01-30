/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:55:41 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/30 18:56:47 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/heredocs.h"
#include <sys/wait.h>

void	here(t_btree *ast, t_dict *d_env)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		rl_clear_history();
		dict_destroy(d_env, free);
		create_heredocs(ast);
		ast_destroy(ast);
		exit (0);
	}
	waitpid(pid, NULL, 0);
}
