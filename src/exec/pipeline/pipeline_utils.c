/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 23:06:24 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/09 11:49:08 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/pipeline.h"
#include "../../../Includes/errors.h"

int	wait_all(t_pipeline *data)
{
	int	i;
	int	status;
	int	final_status;

	status = 0;
	final_status = 0;
	i = 0;
	while (i < data->cmd_count)
	{
		if (data->pids[i] > 0)
		{
			waitpid(data->pids[i], &status, 0);
			if (i == data->cmd_count - 1)
			{
				if (WIFEXITED(status))
					final_status = WEXITSTATUS(status);
				else if (WIFSIGNALED(status))
					final_status = 128 + WTERMSIG(status);
			}
		}
		i++;
	}
	return (final_status);
}

void	close_fds(t_pipeline *data, int i, int is_redir)
{
	if (i < data->cmd_count - 1)
	{
		if (data->p_fd[0] != -1)
			close(data->p_fd[0]);
		if (data->p_fd[1] != -1)
			close(data->p_fd[1]);
		data->p_fd[0] = -1;
		data->p_fd[1] = -1;
	}
	if (is_redir == 1)
	{
		if (data->prev_fd != -1)
			close(data->prev_fd);
	}
}

void	redir_fds(t_pipeline *data, int i)
{
	if (data->in_fd > 2)
	{
		if (dup2(data->in_fd, STDIN_FILENO) == -1)
			ft_print_error(1, NULL, "dup2");
		close(data->in_fd);
	}
	else if (i > 0 && data->prev_fd != -1)
	{
		if (dup2(data->prev_fd, STDIN_FILENO) == -1)
			ft_print_error(1, NULL, "dup2");
	}
	if (data->out_fd > 2)
	{
		if (dup2(data->out_fd, STDOUT_FILENO) == -1)
			ft_print_error(1, NULL, "dup2");
		close(data->out_fd);
	}
	else if (i < data->cmd_count - 1)
	{
		if (dup2(data->p_fd[1], STDOUT_FILENO) == -1)
			ft_print_error(1, NULL, "dup2");
	}
	close_fds(data, i, 1);
}

int	exec_child_built_in(int fctn, t_pipeline *data)
{
	static int (*const	f_built_in[9])(t_ast_node *cmd, t_dict *d_env) = {
	[1] = ft_pwd,
	[2] = ft_env,
	[3] = ft_echo,
	[4] = ft_export_no_args,
	[5] = ft_export,
	[6] = ft_cd,
	[7] = ft_exit,
	[8] = ft_unset};
	int					status;

	status = f_built_in[fctn](data->cmds->content, data->dict);
	ast_destroy(data->ast);
	dict_destroy(data->dict, free);
	free_cmd_list(data->cmds);
	ft_free_arr((void **)data->ev);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	if (data->prev_fd != -1)
		close(data->prev_fd);
	free(data->pids);
	return (status);
}

void	free_child(t_pipeline *data, char *path)
{
	if (path)
		free(path);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	ast_destroy(data->ast);
	dict_destroy(data->dict, free);
	free_cmd_list(data->cmds);
	ft_free_arr((void **)data->ev);
	free(data->pids);
}
