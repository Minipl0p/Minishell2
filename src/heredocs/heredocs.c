/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:46:35 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/20 19:01:40 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/Includes/libft.h"
#include "../../Includes/minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define SIZE_RAND 8

char	*build_name(char name[SIZE_RAND + 6])
{
	int			fd_rand;
	int			i;

	ft_strcat(name, "/tmp/");
	while (1)
	{
		fd_rand = open("/dev/urandom", O_RDONLY);
		if (fd_rand < 0)
			return (NULL);
		if (read(fd_rand, name + 5, SIZE_RAND) != SIZE_RAND)
		{
			close(fd_rand);
			return (NULL);
		}
		close(fd_rand);
		i = -1;
		while (++i < SIZE_RAND)
			name[i] = ((((int)name[i] + 256) % 26) + 'a');
		return (name);
		if (access(name, F_OK) != 0)
			return (name);
	}
}

int	create_heredoc(t_redir **heredocs)
{
	int			fd;
	static char	name[SIZE_RAND + 6] = {0};

	if ((*heredocs)->type != R_HEREDOC || (*heredocs)->target == NULL)
		return (-1);
	build_name(name);
	fd = open(name, O_CREAT, 0777);
	if (fd < 0)
		return (-1);
}

int	find_heredocs(t_btree *ast)
{
	t_redir *head;

	head = ((t_ast_node *)ast->content)->redirs;
	find_heredocs(ast->left);
	while (head != NULL)
	{
		if (head->type == R_HEREDOC)
			create_heredoc(&head);
		head = head->next;
	}
	find_heredocs(ast->right);
}

int	main(void)
{
	char	*name;

	name = build_name();
	if (!name)
		return (1);
	printf("%s\n", name);
	free(name);
	return (0);
}
