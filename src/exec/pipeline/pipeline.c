/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:32:55 by pcaplat           #+#    #+#             */
/*   Updated: 2026/01/27 12:11:32 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"
#include "../../../libft/Includes/libft.h"
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
	if (i == 0)
		dup2(data->in_fd, STDIN_FILENO);
	else
	{
		dup2(data->prev_fd, STDIN_FILENO);
		close(data->prev_fd);
	}
	if (i == data->cmd_count - 1 && data->out_fd != -1)
		dup2(data->out_fd, STDOUT_FILENO);
	else
	{
		dup2(data->p_fd[1], STDOUT_FILENO);
		close(data->p_fd[1]);
		close(data->p_fd[0]);
	}
}
static void	child_process(t_pipeline *data, t_list *cmds, int i)
{
	char	*path;

	redir_fds(data, i);
	close(data->in_fd);
	close(data->out_fd);
	path = parse_path(data->dict, ((t_ast_node *)cmds->content)->argv);
	if (!path)
	{
		printf("cmd : %s\n", ((t_ast_node *)cmds->content)->argv[0]);
		ft_putstr_fd("Error: command not found\n", 2);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		free_cmd_list(data->cmds);
		free(data->pids);
		ft_free_arr((void **)data->ev);
		exit(127);
	}
	execve(path, ((t_ast_node *)cmds->content)->argv, data->ev);
	perror("execve");
	free_cmd_list(data->cmds);
	ft_free_arr((void **)data->ev);
	free(data->pids);
	exit(126);
}

static int	pipeline(t_pipeline *data, t_list *cmds, int i)
{
	if (i < data->cmd_count - 1)
	{
		if (pipe(data->p_fd) == -1)
		{
			perror("Pipe");
			return (-1);
		}
	}
	data->pids[i] = fork();
	if (data->pids[i] == -1)
	{
		perror("Fork");
		return (-1);
	}
	if (data->pids[i] == 0)
	{
//		if (is_built_in((t_ast_node *)cmds->content) == 1)
//			exec_built_in();
		child_process(data, cmds, i);
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

int	run_pipeline(t_list *cmds, t_dict *dict)
{
	t_pipeline	data;
	t_list		*cmd_lst;
	int			i;
	int			status;

	if (init_pipeline(&data, dict, cmds) == -1)
		return (-1);
	cmd_lst = cmds;
	i = 0;
	while (i < data.cmd_count)
	{
		set_fds(&data, cmd_lst);
//		if (i == 0 && is_built_in(((t_ast_node *)cmd_lst->content)) == 0)
//			exec_built_in();
		if (pipeline(&data, cmd_lst, i) == -1)
				break ;
		cmd_lst = cmd_lst->next;
		i++;
	}
	status = wait_all(&data);
	free_cmd_list(data.cmds);
	free(data.pids);
	ft_free_arr((void **)data.ev);
	if (data.in_fd != -1)
		close(data.in_fd);
	if (data.out_fd != -1)
		close(data.out_fd);
	return (status);
}
