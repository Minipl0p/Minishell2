/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 15:20:01 by miniplop          #+#    #+#             */
/*   Updated: 2026/02/02 09:25:14 by miniplop         ###   ########.fr       */
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

#endif
