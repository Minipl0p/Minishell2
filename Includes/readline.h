/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 17:01:32 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/21 15:25:58 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H

# include "ast.h"
# include "../libft/Includes/libft.h"

# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>

char	*read_minish(void);

#endif
