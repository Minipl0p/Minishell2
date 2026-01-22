/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:32:55 by pcaplat           #+#    #+#             */
/*   Updated: 2026/01/22 20:46:05 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"
#include "../../../libft/Includes/libft.h"


static void	close_fds(t_pipeline *data)
{
	close(data->in_fd);
	close(data->p_fd[0]);
	close(data->p_fd[1]);
	close(data->out_fd);
	if (data->prev_fd != -1)
		close(data->prev_fd);
}

static void	wait_all(t_pipeline *data)
{
	int	i;
	int	status;

	close_fds(data);
	status = 0;
	i = 0;
	while (i < data->cmd_count)
	{
		waitpid(data->pids[0], &status, 0);
		i++;
	}
}

static int	child_process(t_pipeline *data, t_list *cmds, int i)
{
	char	*path;

	if (i == 0)
		dup2(data->in_fd, STDIN_FILENO);
	else
		dup2(data->prev_fd, STDIN_FILENO);
	if (i == data->cmd_count - 1)
		dup2(data->out_fd, STDOUT_FILENO);
	else
		dup2(data->p_fd[1], STDOUT_FILENO);
	close_fds(data);
	path = parse_path(data->dict, ((char **)cmds->content));
	if (!path)
		return (-1);
	execve(path, ((char **)cmds->content), data->ev);
	return (-1);
}

static int	pipeline(t_pipeline *data, t_list *cmds, int i)
{
	if (i < data->cmd_count - 1)
	{
		if (pipe(data->p_fd) == -1)
			return (-1);
	}
	data->pids[i] = fork();
	if (data->pids[i] == -1)
		return (-1);
	if (data->pids[i] == 0)
	{
//		if (is_built_in((t_ast_node *)cmds->content) == 1)
//			exec_built_in();
		if (child_process(data, cmds, i) == -1)
			return (-1);
	}
	if (i > 0)
		close(data->prev_fd);
	if (i < data->cmd_count - 1)
	{
		data->prev_fd = data->p_fd[0];
		close(data->p_fd[1]);
	}
	return (1);
}

int	run_pipeline(t_list *cmds, char **ev, t_dict *dict)
{
	t_pipeline	data;
	t_list		*cmd_lst;
	int			i;

	if (init_pipeline(&data, ev, dict, cmds) == -1)
		return (-1);
	cmd_lst = cmds;
	i = 0;
	while (i < data.cmd_count)
	{
		if (set_fds(&data) == -1)
			return (-1);
//		if (i == 0 && is_built_in(((t_ast_node *)cmd_lst->content)) == 0)
//			exec_built_in();
		else
		{
			if (pipeline(&data, cmds, i++) == -1)
				return (-1);
		}
		cmds = cmds->next;
	}
	wait_all(&data);
	return (1);
}
