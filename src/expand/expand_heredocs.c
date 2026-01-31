/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredocs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 18:51:48 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/31 18:53:32 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	explore_heredocs(t_redir *head, t_dict *d_env,
		int (*f)(char **, t_dict *))
{
	int		fd;
	int		err;
	char	*line;
	int		flag;

	fd = open(head->target, O_RDWR, 0644);
	if (fd < 0)
		return (-1);
	flag = 1;
	while (flag || line)
	{
		flag = 0;
		line = get_next_line(fd);
		err = f(&line, d_env);
		if (err < 0)
		{
			free(line);
			close(fd);
			return (-1);
		}
		free(line);
	}
	close(fd);
	return (err);
}

