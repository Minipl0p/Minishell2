/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:05:04 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/20 09:43:35 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"
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

static t_dict	*init(int ac, char **av, char **env)
{
	t_dict				*d_env;
	struct sigaction	sa;

	(void)ac;
	(void)av;
	init_signal(&sa, NULL, MAIN);
	signal(SIGQUIT, SIG_IGN);
	print_banner();
	d_env = init_d_env(env);
	return (d_env);
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

static void	process(t_dict *d_env)
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
		ast = pars(line, d_env);
		free(line);
		if (update_return_value_sig_int(d_env, ast) != 0)
			continue ;
		if (ast)
		{
			ret = exec_ast(ast, d_env, ast);
			unlink_all(ast);
			ast_destroy(ast);
		}
		else
			ret = 0;
		if (update_return_value(ret, d_env) == -1)
			break ;
	}
}

int	main(int ac, char **av, char **env)
{
	t_dict	*d_env;

	d_env = init(ac, av, env);
	if (!d_env)
		return (1);
	process(d_env);
	dict_destroy(d_env, free);
	rl_clear_history();
	return (0);
}
