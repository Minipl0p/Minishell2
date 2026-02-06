/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredocs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 09:36:21 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/06 12:05:31 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/expand.h"
#include "../../Includes/heredocs.h"
#include <unistd.h>

static void	write_in_new_heredocs(char **line, int fd)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		write(fd, line[i], ft_strlen(line[i]));
		write(fd, "\n", 1);
		i++;
	}
}

static char	**expand_heredocs_line(char *str, t_dict *d_env)
{
	char	*step1_vars;
	char	**step2_split;

	step1_vars = expand_str_vars(str, d_env);
	if (!step1_vars)
		return (NULL);
	step2_split = split_words_nquoted(step1_vars, ' ');
	free(step1_vars);
	return (step2_split);
}

static void	replace_target(int old_fd, int new_fd, t_redir *head, char *path)
{
	close(old_fd);
	close(new_fd);
	unlink(head->target);
	free(head->target);
	head->target = path;
}

int	expand_heredocs(t_redir *head, t_dict *d_env)
{
	int		old_fd;
	int		new_fd;
	char	*path;
	char	*line;
	char	**new_line;

	old_fd = open(head->target, O_RDWR, 0644);
	if (old_fd < 0)
		return (-1);
	new_fd = open_tmp_file(&path);
	if (new_fd == -1)
		return (-1);
	line = get_next_line(old_fd);
	while (line)
	{
		new_line = expand_heredocs_line(line, d_env);
		free(line);
		if (!new_line)
			return (-1);
		write_in_new_heredocs(new_line, new_fd);
		ft_free_arr((void **)new_line);
		line = get_next_line(old_fd);
	}
	replace_target(old_fd, new_fd, head, path);
	return (0);
}
