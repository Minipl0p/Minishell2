/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredocs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 09:36:21 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/02 10:37:11 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/expand.h"
#include "../../Includes/heredocs.h"

static int	expand_heredocs(t_redir *head, t_dict *d_env)
{
	int		old_fd;
	int		new_fd;
	int		err;
	char	*line;
	int		flag;

	old_fd = open(head->target, O_RDWR, 0644);
	if (old_fd < 0)
		return (-1);
	new_fd = open_tmp_
	flag = 1;
	while (flag || line)
	{
		flag = 0;
		line = get_next_line(fd);
		err = f(&line, d_env);
		if (err < 0)
		{
			free(line);
			close(fd);
			return (-1);
		}
		free(line);
	}
	close(fd);
	return (err);
}
