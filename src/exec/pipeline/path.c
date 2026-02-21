/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:15:53 by pcaplat           #+#    #+#             */
/*   Updated: 2026/02/21 15:20:05 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/pipeline.h"
#include "../../../Includes/errors.h"

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

static char	*set_local_path(char *cmd, int *perm_error)
{
	char	*path;

	path = str_catsep(".", cmd, '/');
	if (access(path, F_OK | X_OK) == 0)
		return (path);
	if (access(path, F_OK) == 0 && access(path, X_OK) == -1)
		*perm_error = 1;
	free(path);
	return (NULL);
}

static char	*check_cmd_path(char **path_ar, char **cmd, int *perm_error)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (cmd && cmd[0] && path_ar && path_ar[i])
	{
		path = str_catsep(path_ar[i], cmd[0], '/');
		if (!path)
		{
			free(path);
			return (NULL);
		}
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		if (access(path, F_OK) == 0 && access(path, X_OK) == -1)
			*perm_error = 1;
		free(path);
		path = NULL;
		i++;
	}
	return (path);
}

char	*parse_path(t_dict *dict, char **cmd, int *perm_error)
{
	char	**path_ar;
	char	*path;
	char	*tmp;

	if (cmd && cmd[0] && ft_strchr(cmd[0], '/'))
	{
		path = ft_strdup(cmd[0]);
		return (path);
	}
	tmp = dict_get(dict, "PATH");
	if (!tmp)
	{
		path = set_local_path(cmd[0], perm_error);
		return (path);
	}
	path_ar = ft_split(tmp, ':');
	path = check_cmd_path(path_ar, cmd, perm_error);
	if (path_ar)
		ft_free_arr((void *)path_ar);
	return (path);
}
