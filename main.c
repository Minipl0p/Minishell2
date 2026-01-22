/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:05:04 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/22 17:13:53 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"
#include "Includes/pipeline.h"
#include "Includes/print.h"
#include "libft/Includes/ft_dict.h"
#include "libft/Includes/ft_io.h"
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>

static t_btree	*pars(char *line)
{
	t_token	*token_lst;
	t_token	*head;
	t_btree	*ast;

	if (!line)
		return (NULL);
	token_lst = lex(line);
	if (!token_lst)
		return (NULL);
	// display_tokens(token_lst);
	head = token_lst;
	ast = parse_or(&head);
	if (!ast)
	{
		destroy_token(token_lst);
		return (NULL);
	}
	print_ast(ast, 0);
	ft_putendl_fd("\n-----------create heredocs-------------\n", 1);
	create_heredocs(ast);
	print_ast(ast, 0);
	destroy_token(token_lst);
	return (ast);
}

static t_dict	*init(int ac, char **av, char **env)
{
	t_dict	*d_env;
	struct sigaction sa;

	(void)ac;
	(void)av;
	init_signal(&sa, NULL, MAIN);
	print_banner();
	d_env = init_d_env(env);
	return (d_env);
}

int	main(int ac, char **av, char **env)
{
	t_btree	*ast;
	t_dict	*d_env;
	t_list	*cmds;
	char	*line;

	d_env = init(ac, av, env);
	if (!d_env)
		return (1);
	while (1)
	{
		line = read_minish();
		ast = pars(line);
		cmds = NULL;
		if (!line)
		{
			dict_destroy(d_env, free);
			rl_clear_history();
			return (0);
		}
		if (pipe_flatten(ast, &cmds) == 0)
			log_cmd_lst(cmds);
		if (ast)
			ast_destroy(ast);
		if (cmds)
			free_cmd_list(cmds);
		free(line);
	}
	dict_destroy(d_env, free);
	rl_clear_history();
	return (0);
}
