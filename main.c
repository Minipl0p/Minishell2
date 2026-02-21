/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:05:04 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/21 13:55:55 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"
#include "libft/Includes/ft_string.h"
#include <readline/readline.h>

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
