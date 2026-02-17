/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 16:01:16 by pcaplat           #+#    #+#             */
/*   Updated: 2026/02/17 18:56:29 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include <unistd.h>
# include <errno.h>
# include <string.h>
# include "pipeline.h"

# define KQ0 "Comment ?"
# define KQ1 "Vous considérer en tant que ? J'ai pas compris."
# define KQ2 "« En tant que tel » quoi ?"
# define KQ3 "Victime des ? Putain la vache, je comprends pas un mot de ce que\
vous racontez. Allez-y, excusez-moi, reprenez depuis le début je vous écoute."
# define KQ4 "Non mais je sens bien que vous essayez de me dire quelque chose,\
mais... c'est de vous, la phrase, ou vous l'avez entendu, ça ? « Colifichet\
», par exemple, qu'est-ce que... qu'est-ce que c'est pour vous ? Comment \
ça se... comment vous vous le représentez, « colifichet » ?"
# define KQ5 "Non. Déjà, non. Je suis désolé, pas du tout."
# define KQ6 "Non mais non, c'est pas ça !"
# define KQ7 "Comment on dit quoi ? Putain non, là ça y est j'en ai marre là."
# define KQ8 "Non moi je crois qu'il faut que vous arrêtiez d'essayer de dire\
des trucs. Ça vous fatigue, déjà, puis pour les autres, vous vous rendez \
pas compte de ce que c'est. Moi, quand vous faites ça, ça me fout une \
angoisse... je pourrais vous tuer, je crois. De chagrin ! Je vous jure,\
c'est pas bien ! Il faut plus que vous parliez avec des gens."
# define KQ9 "Mais personne dit ça..."
# define KQ10 "Jamais de la vie..."
# define KQ11 "Vous commencez à me les briser menu."
# define KQ12 "C'est pas faux"

void	ft_print_error(int sh_error, char *msg, char *target);
void	exit_path_error(t_ast_node *cmd, t_pipeline *data, int perm_error);
int		check_start_token(t_token *head, t_token *token_lst);
t_btree	*check_end_token(t_btree *ast, t_token *head);
void	print_kaamellot_error(void);
int		update_return_value(int ret, t_dict *d_env);

#endif
