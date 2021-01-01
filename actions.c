/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laskolin <laskolin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 09:06:51 by laskolin          #+#    #+#             */
/*   Updated: 2020/07/16 17:39:26 by laskolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	stay_round(t_wolf *wo)
{
	if (wo->ray->deg >= 360.0)
		wo->ray->deg -= 360.0;
	else if (wo->ray->deg < 0.0)
		wo->ray->deg += 360.0;
}

int		energy(t_wolf *wo)
{
	if (wo->energy > 46)
		wo->energy = 46;
	mlx_put_image_to_window(wo->mlx, wo->win, wo->ban.img, BAN_X, BAN_Y);
	mlx_put_image_to_window(wo->mlx, wo->win, wo->ban2.img, BAN2_X, BAN2_Y);
	if (wo->energy < -5.0)
	{
		wo->lives--;
		if (wo->lives == -1)
		{
			game_over(wo);
			return (0);
		}
		else
			wo->energy = 42.0;
	}
	print_energy(wo);
	compass(wo);
	print_stats(wo);
	return (1);
}

void	look(int key, t_wolf *wo)
{
	if (key == 2 && wo->ray->look >= 0.4)
		wo->ray->look -= 0.2;
	else if (key == 8 && wo->ray->look <= 3.6)
		wo->ray->look += 0.2;
	paint_plane(wo);
	raycast(wo, wo->ray);
	mlx_put_image_to_window(wo->mlx, wo->win, wo->plane, 20, PLANE_H / 4);
	if (wo->ray->look > 1.8)
		wo->gotlife = 0;
	if (wo->ray->look < 0.4)
	{
		mlx_string_put(wo->mlx, wo->win, (PLANE_W + 40) / 2 - 20,
			PLANE_H * 0.50, 0x000000, "HELLO!");
		mlx_string_put(wo->mlx, wo->win, (PLANE_W + 40) / 2 - 170,
			PLANE_H * 0.60, 0x000000, "YOU HAVE FOUND A TOP SECRET MESSAGE.");
		mlx_string_put(wo->mlx, wo->win, (PLANE_W + 40) / 2 - 20,
			PLANE_H * 0.70, 0x000000, "1 UP!");
		if (wo->gotlife == 0)
		{
			wo->lives++;
			wo->gotlife = 1;
			print_stats(wo);
		}
	}
}

void	shrink(int key, t_wolf *wo)
{
	if (key == 32)
		wo->tiny = 10;
	if (key == 16)
		wo->tiny = 2;
	if (key == 17)
		wo->tiny = 1;
	paint_plane(wo);
	raycast(wo, wo->ray);
	mlx_put_image_to_window(wo->mlx, wo->win, wo->plane, 20, PLANE_H / 4);
}
