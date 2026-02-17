/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 14:13:49 by pcaplat           #+#    #+#             */
/*   Updated: 2026/02/17 18:02:02 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_H
# define PIPELINE_H

# include "../libft/Includes/libft.h"
# include "ast.h"
# include "builtin.h"
# include "expand.h"
# include "signals.h"

# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_pipeline
{
	char	**ev;
	t_list	*cmds;
	t_btree	*ast;
	t_dict	*dict;
	pid_t	*pids;
	int		p_fd[2];
	int		cmd_count;
	int		prev_fd;
	int		in_fd;
	int		out_fd;
}			t_pipeline;

//================================UTILS========================================
void	free_cmd_list(t_list *lst);
void	free_child(t_pipeline *data, char *path);
void	redir_fds(t_pipeline *data, int i);
void	close_fds(t_pipeline *data, int i, int is_redir);
int		wait_all(t_pipeline *data, int ret);
int		is_forkable(t_ast_node *cmd);
int		update_return_value(int ret, t_dict *d_env);

//================================BUILDER======================================
int		pipe_flatten(t_btree *ast, t_list **cmds);
int		init_pipeline(t_pipeline *data, t_dict *dict,
			t_btree *ast, t_list *cmds);

//================================PIPELINE=====================================
char	*parse_path(t_dict *dict, char **cmd, int *perm_error);
int		run_pipeline(t_list *cmds, t_dict *dict, t_btree *ast);
int		set_fds(t_pipeline *data, t_list *cmds);
int		exec_ast(t_btree *ast, t_dict *dict, t_btree *root);

//================================BUILTINS=====================================
int		exec_cmd(t_btree *ast, t_dict *dict, t_btree *root);
int		exec_child_built_in(int fctn, t_pipeline *data, t_ast_node *cmd);

#endif
