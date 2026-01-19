/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchazalm <pchazalm@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 15:50:09 by pchazalm          #+#    #+#             */
/*   Updated: 2025/12/30 19:38:53 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GNL_H
# define FT_GNL_H

# include <stdlib.h>
# include <unistd.h>

// Utils
int		ft_strchr_gnl(const char *s, int c);
size_t	ft_strlen_gnl(const char *str);
char	*ft_substr_gnl(char *str, int start, int len);
char	*ft_strdup_gnl(char *str);
void	*ft_calloc_gnl(size_t n, size_t m);

//gnl
char	*get_next_line(int fd);

#endif
