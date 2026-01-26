/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:56:20 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/26 13:07:46 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ast.h"
#include <stdio.h>

static char	*replace(char *src, int start, int len, char *value)
{
	char	*new_str;
	int		len_src;
	int		len_rep;
	char	*rep;

	if (!src || start < 0 || len < 0)
		return (NULL);
	rep = value;
	if (!rep)
		rep = "";
	len_src = ft_strlen(src);
	len_rep = ft_strlen(rep);
	new_str = ft_calloc(sizeof(char), (len_src - len + len_rep + 1));
	if (!new_str)
		return (NULL);
	ft_strlcat(new_str, src, start + 1);
	ft_strcat(new_str, rep);
	ft_strcat(new_str, src + start + len);
	free(src);
	return (new_str);
}

int	find_and_replace(char **str, t_dict	*d_env, int i)
{
	char	*new;
	char	*key;
	int		start;

	start = i;
	i++;
	while ((*str)[i] && !ft_isspace((*str)[i]) && (*str)[i] != '$')
		i++;
	key = ft_strndup((*str) + start + 1, i - start - 1);
	if (!key)
		return (-1);
	new = replace((*str), start, i - start, dict_get(d_env, key));
	free(key);
	if (!new)
		return (-1);
	*str = new;
	i = start;
	return (start);
}

static int	remove_quote(char **str)
{
	int		i;
	char	*new;
	char	*quote;
	char	*quote_end;

	if (!str || !*str)
		return (0);
	quote = ft_strchr(*str, '\'');
	quote_end = ft_strchr(quote + 1, '\'');
	new = replace(*str, (*str) - quote, 1, NULL);
	if (!new)
		return (-1);
	*str = new;
	new = replace(*str, (*str) - quote_end - 1, 1, NULL);
	if (!new)
		return (-1);
	*str = new;
	return (0);
}

static int	expand(char **str, t_dict *d_env)
{
	int		i;

	i = -1;
	while ((*str)[++i])
	{
		if ((*str)[i] == '$')
		{
			i = find_and_replace(str, d_env, i);
			if (i == -1)
				return (-1);
		}
	}
	if (remove_quote(str) == -1)
		return (-1);
	return (0);
}

static int	explore(t_ast_node *n, t_dict *d_env, int (*f)(char **, t_dict *))
{
	int		i;
	int		err;
	t_redir	*head;

	if (n->type == AST_PIPE || n->type == AST_AND || n->type == AST_AND
		|| n->type == AST_PAR_O || n->type == AST_PAR_F)
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
	err = explore(root->content, d_env, expand);
	if (err < 0)
		return (-1);
	err = expand_infix(root->right, d_env);
	if (err < 0)
		return (-1);
	return (0);
}
