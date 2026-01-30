/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:08:34 by pcaplat           #+#    #+#             */
/*   Updated: 2026/01/30 19:01:40 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEX_H
# define LEX_H

# include "../libft/Includes/libft.h"
# include <stdio.h>

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	OR,
	AND,
	L_PAR,
	R_PAR,
	EOF_TOK
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}				t_token;

t_token	*lex(char *input);

t_token	*new_token(t_token_type type, char *content);
char	*set_value(char **input);
void	add_token(t_token **token_lst, t_token *token);
void	destroy_token(t_token *token_lst);
int		create_token(t_token **token_lst, t_token_type type, char *content);
int		is_token(char *c);

#endif
