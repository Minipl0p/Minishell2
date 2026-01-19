/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:59:13 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/19 17:01:25 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DICT_H
# define DICT_H

# include "../../libft/Includes/libft.h"

t_dict	*init_d_env(char **env);
char	**dict_to_env(t_dict *dict);

#endif
