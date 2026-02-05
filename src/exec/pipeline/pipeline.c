/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:32:55 by pcaplat           #+#    #+#             */
/*   Updated: 2026/02/05 17:55:52 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/pipeline.h"

static void	restore_signals()
{
	struct sigaction	sa;

	init_signal(&sa, NULL, MAIN);
}

static void	child_process(t_pipeline *data, t_ast_node *cmd, int i)
{
	char	*path;
	int		fctn;

	signal(SIGINT, SIG_DFL);
	redir_fds(data, i);
	fctn = is_forkable(cmd);
	if (fctn)
	{
		fctn = exec_child_built_in(fctn, data);
		close_fds(data, i, 0);
		exit(fctn);
	}
	path = parse_path(data->dict, cmd->argv);
	if (!path)
	{
		perror("command not found.");
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		free_child(data);
		exit(127);
	}
	execve(path, cmd->argv, data->ev);
	perror("execve");
	free_child(data);
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
		perror("fork");
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
	if (set_fds(data, cmd_lst) == -1)
		*status = -1;
	if (*status != -1 && pipeline(data, cmd_lst, *i) == -1)
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
	status = wait_all(&data);
	restore_signals();
	if (data.prev_fd != -1)
		close(data.prev_fd);
	free(data.pids);
	free_cmd_list(data.cmds);
	ft_free_arr((void **)data.ev);
	return (status);
}
