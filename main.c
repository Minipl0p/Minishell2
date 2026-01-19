/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:05:04 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/19 17:42:10 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

t_btree	*pars(char *line)
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

int	main(int ac, char **av, char **env)
{
	t_btree	*ast;
	t_dict	*d_env;
	char	*line;

	(void)ac;
	(void)av;
	d_env = init_d_env(env);
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
