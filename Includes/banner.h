/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banner.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 12:25:29 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/21 17:10:30 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BANNER_H
# define BANNER_H

# define SIZE 40
# define NB_FRAMES 97

# include "../libft/Includes/libft.h"

# include <unistd.h>
# include <fcntl.h>

int		ft_sleep_exec(char *time_str, int fd);
void	print_jack_black(void);
void	ft_put_pixel(unsigned char id);
void	print_banner(void);

#endif
