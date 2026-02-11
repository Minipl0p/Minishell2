/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 23:00:58 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/11 11:29:11 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/ast.h"
#include "../../Includes/errors.h"
#include <stdio.h>

static int	is_cmd_token(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == WORD)
		return (1);
	if (token->type == REDIR_IN || token->type == REDIR_OUT
		|| token->type == REDIR_APPEND || token->type == REDIR_HEREDOC)
		return (1);
	return (0);
}

static int	add_word(t_ast_node *cmd, t_token **token)
{
	char	**new_argv;
	int		i;

	i = 0;
	while (cmd->argv && cmd->argv[i])
		i++;
	new_argv = ft_calloc(sizeof(char *), i + 2);
	if (!new_argv)
		return (-1);
	i = 0;
	while (cmd->argv && cmd->argv[i])
	{
		new_argv[i] = cmd->argv[i];
		i++;
	}
	new_argv[i] = ft_strdup((*token)->value);
	if (!new_argv[i])
	{
		free(new_argv);
		return (-1);
	}
	free(cmd->argv);
	cmd->argv = new_argv;
	*token = (*token)->next;
	return (0);
}

t_btree	*parse_simple_cmd(t_token **token, t_btree *tree)
{
	t_ast_node	*cmd;

	cmd = (t_ast_node *)tree->content;
	while (*token && is_cmd_token(*token))
	{
		if ((*token)->type == WORD)
		{
			if (add_word(cmd, token) < 0)
			{
				ast_destroy(tree);
				return (NULL);
			}
		}
		else
		{
			if (parse_redir(token, &cmd->redirs) < 0)
			{
				ast_destroy(tree);
				ft_print_error(1, "invalid redirection", NULL);
				return (NULL);
			}
		}
	}
	return (tree);
}

t_btree	*parse_cmd(t_token **token)
{
	t_btree	*new;

	if ((*token)->type == L_PAR)
	{
		new = parse_subtree(token);
		return (new);
	}
	if (*token && (*token)->type == EOF_TOK)
		return (NULL);
	if (!*token || !is_cmd_token(*token))
	{
		ft_print_error(1, "syntaxeeeeeee error", (*token)->value);
		return (NULL);
	}
	new = ast_new(AST_COMMAND);
	if (!new)
		return (NULL);
	new = parse_simple_cmd(token, new);
	return (new);
}
