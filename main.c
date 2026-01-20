/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:05:04 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/20 12:25:14 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"
#include "libft/Includes/ft_dict.h"
#include <fcntl.h>
#include <unistd.h>

static void	handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

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
	display_tokens(token_lst);
	head = token_lst;
	ast = parse_or(&head);
	if (!ast)
	{
		destroy_token(token_lst);
		return (NULL);
	}
	print_ast(ast, 0);
	destroy_token(token_lst);
	return (ast);
}

static t_dict	*init(int ac, char **av, char **env)
{
	t_dict	*d_env;

	(void)ac;
	(void)av;
	setup_signals();
	print_banner();
	d_env = init_d_env(env);
	return (d_env);
}

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
		ast = pars(line);
		if (!line || !ast)
		{
			if (line)
				free(line);
			dict_destroy(d_env, free);
			rl_clear_history();
			return (0);
		}
		ast_destroy(ast);
		free(line);
	}
	dict_destroy(d_env, free);
	rl_clear_history();
	return (0);
}
