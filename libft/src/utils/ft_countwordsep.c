/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countwordsep.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonlogin <tonlogin@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:40:03 by tonlogin          #+#    #+#             */
/*   Updated: 2025/10/23 12:45:30 by pchazalm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_countwordsep(char const *s, char c)
{
	int	count;
	int	flag;

	count = 0;
	flag = 1;
	while (*s)
	{
		if (*s != c && flag)
		{
			flag = 0;
			count++;
		}
		else if (*s == c)
			flag = 1;
		s++;
	}
	return (count);
}
