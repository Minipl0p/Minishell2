/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 14:13:49 by pcaplat           #+#    #+#             */
/*   Updated: 2026/01/28 10:27:16 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_H
# define PIPELINE_H
# include "../libft/Includes/libft.h"

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

//================================BUILDER======================================
int		pipe_flatten(t_btree *ast, t_list **cmds);
int		init_pipeline(t_pipeline *data, t_dict *dict, t_btree *ast, t_list *cmds);

//================================PIPELINE=====================================
char	*parse_path(t_dict *dict, char **cmd);
int		run_pipeline(t_list *cmds, t_dict *dict, t_btree *ast);
int		set_fds(t_pipeline *data, t_list *cmds);
int		exec_ast(t_btree *ast, t_dict *dict);

#endif
