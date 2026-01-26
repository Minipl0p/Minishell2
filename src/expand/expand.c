/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:56:20 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/26 13:08:43 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ast.h"
#include <fcntl.h>
#include <stdio.h>

static char	*expand_key(char *str, int pos, t_dict *d_env)
{
	char	*new;
	char	*value;
	char	*key;
	int		i;
	int		len;

	i = 0;
	while (str[pos + 1 + i] != '_' || ft_isalnum(str[pos + i + 1]))
		i++;
	key = ft_strndup(&str[pos + 1], i);
	if (!key)
		return (NULL);
	value = dict_get(d_env, str);
	new = ft_calloc(sizeof(char), ft_strlen(str) - i + ft_strlen(value) + 1);
	ft_strlcat(new, str, pos - 1);
	ft_strcat(new, value);
	ft_strcat(new, str + pos + ft_strlen(value));
	free(str);
	return (new);
}

static char	*remove_quote(char *str, int pos)
{
	int		i;
	char	*new;

	if (!str)
		return (0);
	new = ft_calloc(sizeof(char), ft_strlen(str));
	if (!new)
		return (NULL);
	ft_strlcat(new, str, pos);
	ft_strcat(new, str + pos + 1);
	free(str);
	return (new);
}

static int	expand_str(char **str, t_dict *d_env)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (!str || !(*str))
		return (-1);
	while ((*str)[i])
	{
		if (flag == 0 && ((*str)[i] == '\'' || (*str)[i] == '\"'))
		{
			flag += ((*str)[i] == '\'') + 2 * ((*str)[i] == '\"');
			*str = remove_quote(*str, i);
		}
		else if (flag != 0 && (*str)[i] == '$')
			*str = expand_key(*str, i, d_env);
		else if ((flag == 1 && (*str)[i] == '\'') || (flag == 2 && (*str)[i] == '\"'))
		{
			flag -= ((*str)[i] == '\'') + 2 * ((*str)[i] == '\"');
			*str = remove_quote(*str, i);
		}
		else
			i++;
		if (!*str)
			return (-1);
	}
	return (0);
}

static	int	explore_heredocs(t_redir *head, t_dict *d_env, int (*f)(char **, t_dict *))
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

static int	explore(t_ast_node *n, t_dict *d_env, int (*f)(char **, t_dict *))
{
	int		i;
	int		err;
	t_redir	*head;

	if (n->type != AST_COMMAND)
		return (0);
	i = 0;
	while (n->argv[i])
	{
		err = f(&(n->argv[i]), d_env);
		if (err < 0)
			return (-1);
		i++;
	}
	head = n->redirs;
	while (head)
	{
		if (head->type == R_HEREDOC)
			err = explore_heredocs(head, d_env, f);
		else
			err = f(&(head->target), d_env);
		if (err < 0)
			return (-1);
		head = head->next;
	}
	return (0);
}

int	expand_infix(t_btree *root, t_dict *d_env)
{
	int	i;
	int	err;

	if (!root)
		return (0);
	err = expand_infix(root->left, d_env);
	if (err < 0)
		return (-1);
	err = explore(root->content, d_env, expand_str);
	if (err < 0)
		return (-1);
	err = expand_infix(root->right, d_env);
	if (err < 0)
		return (-1);
	return (0);
}
