/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:05:04 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/29 12:34:11 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/ast.h"
#include "Includes/dict.h"
#include "Includes/minishell.h"
#include "Includes/pipeline.h"
#include "Includes/print.h"
#include "Includes/readline.h"
#include "libft/Includes/ft_btree.h"
#include "libft/Includes/ft_dict.h"
#include "libft/Includes/ft_io.h"
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>

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
	ast = parse_or(&head);
	if (!ast)
	{
		destroy_token(token_lst);
		return (NULL);
	}
	destroy_token(token_lst);
	here(ast, d_env);
	return (ast);
}

static t_dict	*init(int ac, char **av, char **env)
{
	t_dict				*d_env;
	struct sigaction	sa;

	(void)ac;
	(void)av;
	init_signal(&sa, NULL, MAIN);
	print_banner();
	d_env = init_d_env(env);
	return (d_env);
}

//int		main(int ac, char **av, char **env)
//{
//	t_btree	*ast;
//	t_dict	*d_env;
//	char	*line;
//
//	d_env = init(ac, av, env);
//	if (d_env != -1)
//		return (1);
//	while (1)
//	{
//		line = read_minish();
//		if (!line)
//			break ;
//		ast = pars(line, d_env);
//		if (ast)
//		{
//			exec_ast(ast, d_env);
//			ast_destroy(ast);
//		}
//		fre
//	}
//}

int	main(int ac, char **av, char **env)
{
	t_btree	*ast;
	t_dict	*d_env;
	char	*line;

	d_env = init(ac, av, env);
	if (!d_env)
		return (1);
	while (1)
	{
		line = read_minish();
		ast = pars(line, d_env);
		if (!line)
		{
			ast_destroy(ast);
			dict_destroy(d_env, free);
			rl_clear_history();
			return (0);
		}
		exec_ast(ast, d_env);
		if (ast)
			ast_destroy(ast);
		free(line);
	}
	dict_destroy(d_env, free);
	rl_clear_history();
	return (0);
}
