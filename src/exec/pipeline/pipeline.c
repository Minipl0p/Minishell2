/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:32:55 by pcaplat           #+#    #+#             */
/*   Updated: 2026/01/27 20:05:03 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"
#include "../../../libft/Includes/libft.h"
#include <stdio.h>
#include <unistd.h>

static int	wait_all(t_pipeline *data)
{
	int	i;
	int	status;
	int	final_status;

	status = 0;
	final_status = 0;
	i = 0;
	while (i < data->cmd_count)
	{
		waitpid(data->pids[i], &status, 0);
		if (i == data->cmd_count - 1)
			final_status = (status >> 8) & 0xFF;
		i++;
	}
	return (final_status);
}

static void	redir_fds(t_pipeline *data, int i)
{
	if (data->in_fd > 2)
	{
		dup2(data->in_fd, STDIN_FILENO);
		close(data->in_fd);
	}
	else if (i > 0 && data->prev_fd != -1)
		dup2(data->prev_fd, STDIN_FILENO);
	if (data->out_fd > 2)
	{
		dup2(data->out_fd, STDOUT_FILENO);
		close(data->out_fd);
	}
	else if (i < data->cmd_count - 1)
		dup2(data->p_fd[1], STDOUT_FILENO);
	if (i < data->cmd_count - 1)
	{
		close(data->p_fd[0]);
		close(data->p_fd[1]);
	}
	if (data->prev_fd != -1)
		close(data->prev_fd);
}

static void	child_process(t_pipeline *data, t_ast_node *cmd, int i)
{
	char	*path;

	redir_fds(data, i);
	path = parse_path(data->dict, cmd->argv);
	if (!path)
	{
		ft_putstr_fd("minishell : command not found.\n", 2);
		free(data->pids);
		free_cmd_list(data->cmds);
		ft_free_arr((void **)data->ev);
		exit(127);
	}
	if (execve(path, cmd->argv, data->ev) == -1)
	{
		free(path);
		perror("execve");
		exit(126);
	}
}

static int	pipeline(t_pipeline *data, t_list *cmds, int i)
{
	if (i < data->cmd_count - 1)
	{
		if (pipe(data->p_fd) == -1)
		{
			perror("pipe");
			return (-1);
		}
	}
	data->pids[i] = fork();
	if (data->pids[i] == -1)
	{
		perror("fork");
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
	if (i == -1)
		printf("%p\n", cmds);

	return (0);
}

int	run_pipeline(t_list *cmds, t_dict *dict)
{
	t_list		*cmd_lst;
	t_pipeline	data;
	int			i;
	int			status;

	if (init_pipeline(&data, dict, cmds) == -1)
		return (-1);
	cmd_lst = cmds;
	i = 0;
	while (i < data.cmd_count)
	{
		if (set_fds(&data, cmd_lst) == -1)
			break ;
	//	if (data.cmd_count == 1 && is_built_in(((t_ast_node *)cmd_lst->content))
	//		exec_built_in();
		else
		{
			if (pipeline(&data, cmd_lst, i) == -1)
				break ;
		}
		if (data.in_fd > 2)
			close(data.in_fd);
		if (data.out_fd > 2)
			close(data.out_fd);
		cmd_lst = cmd_lst->next;
		i++;
	}
	status = wait_all(&data);
	if (data.prev_fd != -1)
		close(data.prev_fd);
	free(data.pids);
	free_cmd_list(data.cmds);
	ft_free_arr((void **)data.ev);
	return (status);
}
