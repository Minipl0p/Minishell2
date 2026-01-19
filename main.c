/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:05:04 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/19 16:22:23 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "Includes/ast.h"
#include "libft/Includes/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

t_dict	*init_d_env(char **env);
char	*read_minish(void);

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
		if (line && !ft_strncmp(line, "exit", 4))
		{
			free(line);
			dict_destroy(d_env, free);
			rl_clear_history();
			return (0);
		}
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
