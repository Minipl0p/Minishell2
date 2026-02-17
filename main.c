/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:05:04 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/17 17:42:02 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/errors.h"
#include "Includes/lex.h"
#include "Includes/minishell.h"
#include "libft/Includes/ft_io.h"
#include <readline/readline.h>

int	update_return_value(int ret, t_dict *d_env)
{
	char	*exit_status;

	exit_status = ft_itoa(ret);
	if (!exit_status)
		return (-1);
	dict_set(d_env, "?", exit_status, free);
	return (0);
}

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
	ast = create_ast(&head, d_env);
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
	// print_banner();
	d_env = init_d_env(env);
	return (d_env);
}

static void	process(t_dict *d_env)
{
	char	*line;
	int		ret;
	t_btree	*ast;

	while (1)
	{
		line = read_minish(d_env);
		if (!line)
			break ;
		ast = pars(line, d_env);
		free(line);
		if (ast)
		{
			ret = exec_ast(ast, d_env, ast);
			unlink_all(ast);
			ast_destroy(ast);
			if (update_return_value(ret, d_env) == -1)
				break ;
		}
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
