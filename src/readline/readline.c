/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:28:59 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/19 17:52:48 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/readline.h"

static char	*get_prompt(void)
{
	char	*cwd;
	char	*base;
	char	*prompt;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		cwd = ft_strdup("?");
		if (!cwd)
			return (cwd);
		prompt = ft_strjoin(cwd, ":🐌>");
		free(cwd);
		return (prompt);
	}
	base = ft_strrchr(cwd, '/');
	if (!base || !*(base + 1))
		base = cwd;
	else
		base++;
	prompt = ft_strjoin(base, ": 🐌 > ");
	free(cwd);
	return (prompt);
}

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

char	*read_minish(void)
{
	char	*line;
	char	*prompt;

	setup_signals();
	prompt = get_prompt();
	if (!prompt)
		return (NULL);
	line = readline(prompt);
	free(prompt);
	if (!line)
		return (NULL);
	if (*line)
		add_history(line);
	return (line);
}
