/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:32:55 by pcaplat           #+#    #+#             */
/*   Updated: 2026/02/17 18:12:43 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/pipeline.h"
#include "../../../Includes/errors.h"

static void	restore_signals(void)
{
	struct sigaction	sa;

	init_signal(&sa, NULL, MAIN);
	signal(SIGPIPE, SIG_DFL);
}

static void	child_process(t_pipeline *data, t_ast_node *cmd, int i)
{
	char	*path;
	int		perm_error;
	int		fctn;

	signal(SIGINT, SIG_DFL);
	redir_fds(data, i);
	fctn = is_forkable(cmd);
	if (fctn)
	{
		fctn = exec_child_built_in(fctn, data, cmd);
		close_fds(data, i, 0);
		exit(fctn);
	}
	perm_error = 0;
	path = parse_path(data->dict, cmd->argv, &perm_error);
	if (!path)
		exit_path_error(cmd, data, perm_error);
	execve(path, cmd->argv, data->ev);
	ft_print_error(1, NULL, cmd->argv[0]);
	free_child(data, path);
	exit(126);
}

static int	pipeline(t_pipeline *data, t_list *cmds, int i)
{
	if (i < data->cmd_count - 1)
	{
		if (pipe(data->p_fd) == -1)
			return (-1);
	}
	signal(SIGINT, SIG_IGN);
	data->pids[i] = fork();
	if (data->pids[i] == -1)
	{
		close_fds(data, i, 0);
		return (-1);
	}
	if (data->pids[i] == 0)
		child_process(data, ((t_ast_node *)cmds->content), i);
	if (data->prev_fd != -1)
		close(data->prev_fd);
	if (i < data->cmd_count - 1)
	{
		data->prev_fd = data->p_fd[0];
		close(data->p_fd[1]);
	}
	else
		data->prev_fd = -1;
	return (0);
}

static void	run_pipeline_step(t_pipeline *data, t_list *cmd_lst,
		int *status, int *i)
{
	*status = 0;
	if (set_fds(data, cmd_lst) == -1)
	{
		data->pids[*i] = -1;
		*status = -1;
	}
	if (*status >= 0 && pipeline(data, cmd_lst, *i) == -1)
		*status = -1;
	if (data->in_fd > 2)
		close(data->in_fd);
	if (data->out_fd > 2)
		close(data->out_fd);
	data->in_fd = -1;
	data->out_fd = -1;
	(*i)++;
}

int	run_pipeline(t_list *cmds, t_dict *dict, t_btree *ast)
{
	t_list		*cmd_lst;
	t_pipeline	data;
	int			i;
	int			status;

	if (init_pipeline(&data, dict, ast, cmds) == -1)
		return (-1);
	data.in_fd = -1;
	data.out_fd = -1;
	cmd_lst = cmds;
	status = 0;
	i = 0;
	while (i < data.cmd_count)
	{
		run_pipeline_step(&data, cmd_lst, &status, &i);
		cmd_lst = cmd_lst->next;
	}
	status = wait_all(&data, status);
	restore_signals();
	if (data.prev_fd != -1)
		close(data.prev_fd);
	free(data.pids);
	free_cmd_list(data.cmds);
	ft_free_arr((void **)data.ev);
	return (status);
}
