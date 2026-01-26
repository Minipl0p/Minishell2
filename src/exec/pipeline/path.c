/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:15:53 by pcaplat           #+#    #+#             */
/*   Updated: 2026/01/26 23:01:16 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"
#include "../../../libft/Includes/libft.h"

static char	*str_catsep(char *s1, char *s2, char sep)
{
	char	*str;
	int		i;
	int		j;
	int		len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 2;
	str = ft_calloc(len, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i++] = sep;
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

static char	*check_cmd_path(char **path_ar, char **cmd)
{
	char	*path;
	int		i;

	i = 0;
	while (path_ar[i])
	{
		path = str_catsep(path_ar[i], cmd[0], '/');
		if (!path)
		{
			free(path);
			return (NULL);
		}
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	*parse_path(t_dict *dict, char **cmd)
{
	char	**path_ar;
	char	*path;

	path_ar = dict_get(dict, "PATH");
	if (!path_ar)
		return (NULL);
	path = check_cmd_path(path_ar, cmd);
	ft_free_arr((void *)path_ar);
	return (path);
}
