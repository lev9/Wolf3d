/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laskolin <laskolin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 09:06:51 by laskolin          #+#    #+#             */
/*   Updated: 2020/07/16 17:39:26 by laskolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	print_stats(t_wolf *wo)
{
	char	*str;
	int		b;
	int		h;

	if (wo->score < 0)
		wo->score = 0;
	mlx_put_image_to_window(wo->mlx, wo->win, wo->ban.img, BAN_X, BAN_Y);
	b = BAN_X;
	h = PLANE_H;
	str = ft_itoa(wo->world);
	mlx_string_put(wo->mlx, wo->win, b + 11, h * 1.25 + 17, 0xFFFFFF, str);
	free(str);
	str = ft_itoa(wo->score);
	mlx_string_put(wo->mlx, wo->win, b + 52, h * 1.25 + 17, 0xFFFFFF, str);
	free(str);
	str = ft_itoa(wo->lives);
	mlx_string_put(wo->mlx, wo->win, b + 94, h * 1.25 + 17, 0xFFFFFF, str);
	free(str);
}

void	print_energy(t_wolf *wo)
{
	int		y;
	int		x;

	y = 0;
	{
		while (y < 11)
		{
			x = 0;
			while (x < wo->energy)
			{
				mlx_pixel_put(wo->mlx, wo->win, BAN2_X + 14 + x,
				BAN2_Y + 14 + y, energy_color(x / 3));
				x++;
				if (((y == 0 || y == 1 || y == 9 || y == 10) && x == 44))
					break ;
			}
			y++;
		}
	}
}

void	compass(t_wolf *wo)
{
	int		alpha;
	int		x;
	int		y;

	x = BAN2_X + 90;
	y = BAN2_Y + 6;
	alpha = wo->ray->deg + 30;
	if (alpha > 360)
		alpha -= 360;
	if (alpha < 0)
		alpha += 360;
	if (alpha >= 45 && alpha < 135)
		mlx_put_image_to_window(wo->mlx, wo->win, wo->north.img, x, y);
	else if (alpha >= 135 && alpha < 225)
		mlx_put_image_to_window(wo->mlx, wo->win, wo->east.img, x, y);
	else if (alpha >= 225 && alpha < 315)
		mlx_put_image_to_window(wo->mlx, wo->win, wo->south.img, x, y);
	else
		mlx_put_image_to_window(wo->mlx, wo->win, wo->west.img, x, y);
}

void	paint_plane(t_wolf *wo)
{
	int		i;

	i = 0;
	while (i < PLANE_W * PLANE_H)
	{
		if (wo->world == 1)
			wo->planebuf[i] = 0x000501;
		if (wo->world == 2)
		{
			if (i < PLANE_W * (PLANE_H / wo->ray->look))
				wo->planebuf[i] = 0xffd6d6;
			else
				wo->planebuf[i] = 0x4d4d4d;
		}
		if (wo->world == 3)
		{
			if (i < PLANE_W * (PLANE_H / wo->ray->look))
				wo->planebuf[i] = 0xb0faff;
		}
		i++;
	}
}

int		check_fd(int fd)
{
	if (fd < 0)
		return (errormessage(2));
	return (1);
}
