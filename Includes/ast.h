/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 23:34:22 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/17 17:32:31 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "../libft/Includes/libft.h"
# include "lex.h"

//=================================ENUMS========================================
typedef enum e_ast_type
{
	AST_COMMAND,
	AST_AND,
	AST_OR,
	AST_SUBTREE,
	AST_PIPE
}	t_ast_type;

typedef enum e_redir_type
{
	R_IN,
	R_OUT,
	R_APPEND,
	R_HEREDOC
}	t_redir_type;
//==============================================================================

//=================================STRUCTS======================================
typedef struct s_redir
{
	t_redir_type		type;
	char				*target;
	char				*delim;
	int					expand;
	struct s_redir		*next;
}	t_redir;

typedef struct s_ast_node
{
	t_ast_type	type;
	char		**argv;
	t_redir		*redirs;
}				t_ast_node;
//=============================================================================

//=================================TOOLS=======================================
t_btree	*ast_link_binary(t_ast_type type, t_btree *left, t_btree *right);
void	ast_destroy(t_btree *root);
t_btree	*ast_new(t_ast_type type);
t_btree	*parse_error(char *msg);
void	free_redirs(t_redir *redir);
int		is_cmd_token(t_token *token);
//=============================================================================

//=================================PARS========================================
t_btree	*parse_pipe(t_token **token, t_dict *d_env);
t_btree	*parse_cmd(t_token **token, t_dict *d_env);
t_btree	*parse_subtree(t_token **token, t_dict *d_env);
int		parse_redir(t_token **token, t_redir **redir);
t_btree	*create_ast(t_token **token, t_dict *d_env);
//=============================================================================

#endif
