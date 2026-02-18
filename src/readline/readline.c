/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:28:59 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/18 10:08:00 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/readline.h"
#include "../../Includes/errors.h"

static char	*get_prompt(t_dict *d_env)
{
	char	*cwd;
	char	*base;
	char	*prompt;

	cwd = dict_get(d_env, "PWD");
	if (!cwd)
	{
		cwd = ft_strdup("?");
		if (!cwd)
			return (cwd);
		prompt = ft_strjoin(cwd, ": /` ");
		free(cwd);
		return (prompt);
	}
	cwd = ft_strdup(cwd);
	base = ft_strrchr(cwd, '/');
	if (!base || !*(base + 1))
		base = cwd;
	else
		base++;
	prompt = ft_strjoin(base, "\001: \002 ⛏ ");
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
