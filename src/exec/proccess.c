/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccess.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchazalm <pchazalm@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 14:55:08 by pchazalm          #+#    #+#             */
/*   Updated: 2026/02/20 16:51:34 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"
#include <readline/readline.h>

extern int	g_stop;

static t_btree	*pars(char *line, t_dict *d_env)
{
	t_token	*token_lst;
	t_token	*head;
	t_btree	*ast;

	if (!line)
		return (NULL);
	token_lst = lex(line);
	if (!token_lst)
		return (NULL);
	head = token_lst;
	if (check_start_token(head, token_lst) < 0)
		return (NULL);
	ast = create_ast(&head);
	ast = check_end_token(ast, head);
	if (!ast)
	{
		destroy_token(token_lst);
		return (NULL);
	}
	destroy_token(token_lst);
	create_heredocs(ast, d_env, ast);
	return (ast);
}

static int	update_return_value_sig_int(t_dict *d_env, t_btree *ast)
{
	if (g_stop == 1)
	{
		update_return_value(130, d_env);
		g_stop = 0;
		if (ast)
		{
			unlink_all(ast);
			ast_destroy(ast);
		}
		return (1);
	}
	return (0);
}

static void	process_step(t_btree *ast, int *ret, t_dict *d_env)
{
	if (ast)
	{
		*ret = exec_ast(ast, d_env, ast);
		unlink_all(ast);
		ast_destroy(ast);
	}
	else
		*ret = 2;
}

void	process(t_dict *d_env)
{
	char	*line;
	int		ret;
	t_btree	*ast;

	while (1)
	{
		line = read_minish(d_env);
		update_return_value_sig_int(d_env, NULL);
		if (!line)
			break ;
		if (line && ft_strcmp(line, "") == 0)
			continue ;
		ast = pars(line, d_env);
		free(line);
		if (update_return_value_sig_int(d_env, ast) != 0)
			continue ;
		process_step(ast, &ret, d_env);
		if (update_return_value(ret, d_env) == -1)
			break ;
	}
}
