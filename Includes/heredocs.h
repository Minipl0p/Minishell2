/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 12:01:39 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/22 12:43:46 by miniplop         ###   ########.fr       */
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
# include <signal.h>

int		write_heredoc(int fd, t_redir *redir);
int		create_heredocs(t_btree *ast);
void	unlink_all(t_btree *ast);

#endif
