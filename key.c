/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laskolin <laskolin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 09:06:51 by laskolin          #+#    #+#             */
/*   Updated: 2020/07/16 17:39:26 by laskolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	game_over(t_wolf *wo)
{
	mlx_clear_window(wo->mlx, wo->win);
	mlx_string_put(wo->mlx, wo->win, PLANE_W / 2 - 70, PLANE_H / 2, 0xe85d5d,
		"G A M E  O V E R !");
	mlx_string_put(wo->mlx, wo->win, PLANE_W / 2 - 71, PLANE_H / 2, 0xe85d5d,
		"G A M E  O V E R !");
	mlx_string_put(wo->mlx, wo->win, PLANE_W / 2 - 72, PLANE_H / 2, 0xe85d5d,
		"G A M E  O V E R !");
	mlx_string_put(wo->mlx, wo->win, PLANE_W / 2 - 225, PLANE_H / 2 + 80,
		0xFFFFFF, "P R E S S   S P A C E   T O   S T A R T   A G A I N");
	mlx_string_put(wo->mlx, wo->win, PLANE_W / 2 - 226, PLANE_H / 2 + 80,
		0xFFFFFF, "P R E S S   S P A C E   T O   S T A R T   A G A I N");
	wo->started = 0;
}

void	enemy_speaks(t_wolf *wo)
{
	int	x;
	int	y;

	x = (PLANE_W + 40) / 2 + 150;
	y = PLANE_H * 0.25 + 20;
	if (wo->world == 1)
		mlx_string_put(wo->mlx, wo->win, x, y, 0xFFFFFF,
		"PRESS F / G TO SHOOT!");
	if (wo->world == 2)
		mlx_string_put(wo->mlx, wo->win, x - 100, y, 0x000000,
			"PRESS D / C TO STRETCH YOUR NECK!");
	if (wo->world == 3)
		mlx_string_put(wo->mlx, wo->win, x, y, 0x000000,
			"PRESS T / Y / U TO RESIZE!");
}

void	act(int key, t_wolf *wo)
{
	if ((key == 5 || key == 3 || key == 4) && wo->ray->look == 2.0)
	{
		shoot(key, wo);
		if (wo->world == 1 && wo->ray->look == 2.0 && wo->ray->enempd
			< 1200.0 && wo->ray->enempd > 0)
			mlx_string_put(wo->mlx, wo->win, 650, 200, 0xFFFFFF,
			"NOT ME YOU *****");
	}
	else if (key == 6)
		lights_out(wo);
	else if (key == 7 && wo->lights == 0)
		change_world(wo);
	else if (key == 123)
		turn_left(wo);
	else if (key == 124)
		turn_right(wo);
	else if (key == 126)
		walk(wo);
	else if (key == 125)
		walk_back(wo);
	else if (key == 16 || key == 17 || key == 32)
		shrink(key, wo);
	else if (wo->world == 2 && (key == 2 || key == 8))
		look(key, wo);
}

int		deal_key(int key, t_wolf *wo)
{
	if (key == 53)
		end(wo);
	if (wo->started == 0 && key == 49)
		continue_screen(wo);
	if (wo->started == 1)
	{
		if (wo->lights == 0)
		{
			if (key == 7)
				change_world(wo);
		}
		else
		{
			act(key, wo);
			if (wo->ray->look > 1.0 && wo->ray->enempd < 1200.0 &&
				wo->ray->enempd > 0)
				enemy_speaks(wo);
		}
	}
	return (1);
}
