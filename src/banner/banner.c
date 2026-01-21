/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniplop <miniplop@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 12:27:34 by miniplop          #+#    #+#             */
/*   Updated: 2026/01/21 12:44:04 by miniplop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/banner.h"
#include "../../Includes/signals.h"

extern volatile int g_stop;

void	ft_render_frame(unsigned char *buffer)
{
	int	i;

	write(1, "\033[H", 3);
	i = 0;
	while (i < SIZE * SIZE)
	{
		if (i > 0 && i % SIZE == 0)
			write(1, "\033[0m\n", 5);
		ft_put_pixel(buffer[i]);
		i++;
	}
	write(1, "\033[0m\n", 5);
}

int	ft_play_loading(int fd)
{
	int					i;
	unsigned char		buffer[SIZE * SIZE];
	struct sigaction	sa;
	struct sigaction	old_sa;

	init_signal(&sa, &old_sa, BANNER);
	write(1, "\033[2J\033[?25l", 10);
	i = 0;
	while (i < NB_FRAMES && !g_stop)
	{
		if (read(fd, buffer, SIZE * SIZE) != SIZE * SIZE)
			return (-1);
		ft_render_frame(buffer);
		if (ft_sleep_exec("0.02") < 0)
			return (-1);
		i++;
	}
	write(1, "\033[?25h", 6);
	close(fd);
	sigaction(SIGINT, &old_sa, NULL);
	if (g_stop == 1)
		return (-1);
	return (0);
}

void	print_banner(void)
{
	int	success;
	int	fd;

	success = 1;
	if (access("/bin/sleep", X_OK) < 0)
		success = 0;
	fd = open("./src/banner/mineshell_assets.bin", O_RDONLY);
	if (fd < 0)
		success = 0;
	if (!success || ft_play_loading(fd) < 0)
	{
		write(1, "\033[H\033[2J\033[?25h", 10);
		if (fd > 0)
			close(fd);
		print_jack_black();
		if (g_stop == 1)
		{
			g_stop = 0;
			ft_putstr_fd("\n\033[1;33m >> You thought you ", 1);
			ft_putstr_fd("tricked Mine-Shell, but it’s Jack Black who ", 1);
			ft_putendl_fd("just tricked YOU!\033[0m\n\n", 1);
		}
		else
		{
			ft_putstr_fd("\n\033[1;33m >> Jack Black is ", 1);
			ft_putendl_fd("keeping the assets for himself !\033[0m\n\n", 1);
		}
	}
	else
		write(1, "\n", 1);
}
