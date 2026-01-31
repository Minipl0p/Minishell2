/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:28:59 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/31 11:09:21 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/readline.h"

static char	*get_prompt(t_dict *d_env)
{
	char	*cwd;
	char	*base;
	char	*prompt;

	cwd = ft_strdup(dict_get(d_env, "PWD"));
	if (!cwd)
	{
		cwd = ft_strdup("?");
		if (!cwd)
			return (cwd);
		prompt = ft_strjoin(cwd, ":⛏️> ");
		free(cwd);
		return (prompt);
	}
	base = ft_strrchr(cwd, '/');
	if (!base || !*(base + 1))
		base = cwd;
	else
		base++;
	prompt = ft_strjoin(base, ": ⛏️ ");
	free(cwd);
	return (prompt);
}

char	*read_minish(t_dict *d_env)
{
	char	*line;
	char	*prompt;

	prompt = get_prompt(d_env);
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
