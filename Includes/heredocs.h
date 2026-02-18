/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 12:01:39 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/18 10:29:46 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOCS_H
# define HEREDOCS_H

# include "signals.h"
# include "ast.h"
# include "../libft/Includes/libft.h"

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

int		write_heredoc(int fd, t_redir *redir);
int		create_heredocs(t_btree *ast, t_dict *d_env, t_btree *root);
void	unlink_all(t_btree *ast);
void	here(t_btree *ast, t_dict *d_env);
int		open_tmp_file(char **path);
char	*remove_hered_quote(char *s, int i);
void	wait_heredoc(struct sigaction *sa, int pid);

#endif
