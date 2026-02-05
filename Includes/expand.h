/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 15:20:01 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/05 11:49:04 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "ast.h"
# include <fcntl.h>
# include <stdio.h>

int		expand_flatten(t_list *cmds, t_dict *env);
int		expand_argv_array(char ***argv_ptr, t_dict *env);
int		process_expand(char *str, t_list **final_list, t_dict *d_env);
char	*expand_str_vars(char *old_str, t_dict *d_env);
char	**split_words_nquoted(char const *s, char c);
int		expand_heredocs(t_redir *head, t_dict *d_env);
int		add_to_expand_list(t_list **e_lst, char *str);
int		expand_redir_list(t_redir *head, t_dict *env);

int		e_wildcard_unquote(char *str, t_list **expand_lst);
int		trunc_start(t_list **dir_lst, char *arg);
int		trunc_middle(t_list **dir_lst, char *arg);
void	trunc_last(t_list **dir_lst, char *arg);

void	remove_lst(t_list **dir_lst, t_list *to_remove);
int		ft_strlen_sep_skip(char *str, char sep);
char	*ft_strcpy_sep_skip(char *str, char sep, int len);

void	remove_quotes_in_list(t_list *lst);

#endif
