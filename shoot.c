/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laskolin <laskolin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 09:06:51 by laskolin          #+#    #+#             */
/*   Updated: 2020/07/16 17:39:26 by laskolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	lazer(int a, int col, t_wolf *wo)
{
	while (a > 0)
	{
		mlx_pixel_put(wo->mlx, wo->win, DUDE_XX + 32, DUDE_YY - a, col);
		a--;
	}
}

int		sized_a(int tiny)
{
	int		a;

	if (tiny == 10)
		a = 290;
	if (tiny == 2)
		a = 300;
	if (tiny == 1)
		a = 310;
	return (a);
}

int		destroy_wall(int i, t_wolf *wo)
{
	int	col;
	int	lazerpoint;
	int	n;

	n = wo->middle;
	lazerpoint = (DUDE_YY - i - 5 - PLANE_H / 4) * PLANE_W + DUDE_XX + 12;
	col = wo->planebuf[lazerpoint];
	if (col != 0x000501 && col != 0x4d4d4d && (wo->maze[n] == 9 ||
		(wo->maze[n] == 1 && wo->maze[n + 1] != 9 && wo->maze[n - 1] != 9 &&
		wo->maze[n + wo->maze_w] != 9 && wo->maze[n - wo->maze_w] != 9 &&
		wo->maze[n + 1] != 8 && wo->maze[n - 1] != 8 &&
		wo->maze[n + wo->maze_w] != 8 && wo->maze[n - wo->maze_w] != 8)) &&
		n % wo->maze_w >= 1 && n % wo->maze_w < wo->maze_w - 1 &&
		n < wo->maze_w * (wo->maze_h - 1) && n > wo->maze_w)
	{
		wo->maze[wo->middle] = 0;
		wo->energy -= 5.0;
		wo->score -= 1;
		paint_plane(wo);
		raycast(wo, wo->ray);
		mlx_put_image_to_window(wo->mlx, wo->win, wo->plane, 20, 150);
		return (1);
	}
	return (0);
}

int		build_wall(int key, t_wolf *wo)
{
	int		try_x;
	int		try_y;

	wo->facing = 0;
	try_x = (wo->ray->dude_x - cos((wo->ray->deg + FOV / 2) * M_PI / 180) *
		2000) / SIZE;
	try_y = (wo->ray->dude_y - sin((wo->ray->deg + FOV / 2) * M_PI / 180) *
		2000) / SIZE;
	if (wo->maze[try_y * wo->maze_w + try_x] == 0 && try_x >= 0 &&
		try_x < wo->maze_w && try_y >= 0 && try_y < wo->maze_h)
	{
		if (key == 3 || wo->world == 1)
			wo->maze[try_y * wo->maze_w + try_x] = 1;
		else if (key == 4)
			wo->maze[try_y * wo->maze_w + try_x] = 9;
		wo->energy += 5.0;
		wo->score += 1;
		if (wo->score % 5 == 0)
			wo->lives++;
		paint_plane(wo);
		raycast(wo, wo->ray);
		mlx_put_image_to_window(wo->mlx, wo->win, wo->plane, 20, 150);
		return (1);
	}
	return (0);
}

void	shoot(int key, t_wolf *wo)
{
	int		i;
	int		a;
	int		color;

	a = sized_a(wo->tiny);
	color = 0X00FF00;
	if (key == 5)
		color = 0xFF00FF;
	i = 0;
	while (i < a)
	{
		mlx_pixel_put(wo->mlx, wo->win, DUDE_XX + 32, DUDE_YY - i, 0xFFFFFF);
		if ((i > 0 && key == 5 && destroy_wall(i, wo) == 1) || ((key == 4 ||
		key == 3) && build_wall(key, wo) == 1))
		{
			lazer(a, color, wo);
			energy(wo);
			break ;
		}
		i++;
	}
}
