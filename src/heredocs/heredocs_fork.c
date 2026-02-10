/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:55:41 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/10 10:38:28 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/heredocs.h"
#include "../../Includes/errors.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

extern int	g_stop;

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
			s = remove_hered_quote(s, i);
		}
		else if (s && ((*f_quote == 1 && s[i] == '\'')
				|| (*f_quote == 2 && s[i] == '\"')))
		{
			*f_quote = 0;
			s = remove_hered_quote(s, i);
		}
		else
			i++;
	}
	return (s);
}

static char	*clean_delim(char *delim, int *expand)
{
	int		f_quote;
	char	*s;

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
	return (s);
}

static int	open_heredocs(t_redir *redir)
{
	char	*path;
	int		fd;

	redir->delim = clean_delim(redir->target, &redir->expand);
	if (!redir->delim)
		return (1);
	g_stop = 0;
	fd = open_tmp_file(&path);
	if (fd < 0)
		return (1);
	close(fd);
	free(redir->target);
	redir->target = path;
	return (0);
}

static void	fork_heredocs(t_redir *redir, t_dict *d_env, t_btree *root)
{
	int					pid;
	int					fd;
	struct sigaction	sa;

	open_heredocs(redir);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	init_signal(&sa, NULL, HEREDOCS);
	if (pid == 0)
	{
		rl_clear_history();
		dict_destroy(d_env, free);
		fd = open(redir->target, O_WRONLY, O_TRUNC);
		if (fd == -1)
			ft_print_error(1, NULL, "open");
		if (fd != -1)
		{
			write_heredoc(fd, redir);
			close(fd);
		}
		ast_destroy(root);
		exit (0);
	}
	waitpid(pid, NULL, 0);
	init_signal(&sa, NULL, MAIN);
}

int	create_heredocs(t_btree *ast, t_dict *d_env, t_btree *root)
{
	t_ast_node	*cmd;
	t_redir		*redir;

	if (!ast)
		return (0);
	if (create_heredocs(ast->left, d_env, root))
		return (1);
	cmd = ast->content;
	if (cmd->type == AST_COMMAND)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == R_HEREDOC)
				fork_heredocs(redir, d_env, root);
			redir = redir->next;
		}
	}
	return (create_heredocs(ast->right, d_env, root));
}
