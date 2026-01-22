/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_write.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 11:16:24 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/22 22:29:09 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/heredocs.h"
#include <readline/readline.h>
#include <unistd.h>

extern int	g_stop;

void	unlink_all(t_btree *ast)
{
	t_ast_node	*cmd;
	t_redir		*head;

	if (!ast)
		return ;
	unlink_all(ast->left);
	cmd = ast->content;
	if (cmd->type == AST_COMMAND)
	{
		head = cmd->redirs;
		while (head)
		{
			if (head->type == R_HEREDOC && head->target)
				unlink(head->target);
			head = head->next;
		}
	}
	unlink_all(ast->right);
}

char	*remove_quote(char *s, int i)
{
	char	*new_string;
	int		len;

	len = ft_strlen(s);
	new_string = ft_calloc(sizeof(char), len);
	if (!new_string)
		return (NULL);
	ft_strlcat(new_string, s, i + 1);
	ft_strcat(new_string, &s[i] + 1);
	free(s);
	return (new_string);
}

char	*step_delim(char *delim, int *f_quote)
{
	int		i;
	char	*s;

	s = ft_strdup(delim);
	*f_quote = -1;
	i = 0;
	while (s && s[i])
	{
		if (s && *f_quote <= 0 && (s[i] == '\'' || s[i] == '\"'))
		{
			*f_quote = 2;
			if (s[i] == '\'')
				*f_quote = 1;
			s = remove_quote(s, i);
		}
		else if (s && ((*f_quote == 1 && s[i] == '\'')
				|| (*f_quote == 2 && s[i] == '\"')))
		{
			*f_quote = 0;
			s = remove_quote(s, i);
		}
		else
			i++;
	}
	return (s);
}

static char	*clean_delim(char *delim, int *expand)
{
	int		f_quote;
	int		len;
	char	*s;
	char	*final_delim;

	*expand = 0;
	s = step_delim(delim, &f_quote);
	if (f_quote == -1)
		*expand = 1;
	else if (f_quote != 0)
	{
		free(s);
		s = NULL;
		return (s);
	}
	len = ft_strlen(s);
	final_delim = ft_calloc(sizeof(char), len + 1 + 1);
	if (!final_delim)
		return (NULL);
	ft_strcat(final_delim, s);
	free(s);
	final_delim[len] = '\n';
	return (final_delim);
}

int	write_heredoc(int fd, t_redir *redir)
{
	char	*line;
	char	*delim;

	delim = clean_delim(redir->target, &redir->expand);
	if (!delim)
		return (1);
	while (1)
	{
		line = readline("> ");
		if (!line || g_stop)
			break ;
		if (!ft_strcmp(line, delim))
			break ;
		ft_putendl_fd(line, fd);
		free(line);
	}
	free(delim);
	free(line);
	if (g_stop)
	{
		errno = EINTR;
		return (1);
	}
	return (0);
}
