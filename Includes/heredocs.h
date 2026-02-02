/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 12:01:39 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/02 10:37:17 by miniplop         ###   ########.fr       */
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
int		create_heredocs(t_btree *ast);
void	unlink_all(t_btree *ast);
void	here(t_btree *ast, t_dict *d_env);
int		open_tmp_file(char **path);

#endif
