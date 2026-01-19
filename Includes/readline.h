/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 17:01:32 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/19 17:03:35 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef READLINE_H
# define READLINE_H

# include "ast.h"
# include "../../libft/Includes/libft.h"

# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>

t_dict	*init_d_env(char **env);
char	**dict_to_env(t_dict *dict);

#endif
