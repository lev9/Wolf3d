/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laskolin <laskolin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 09:06:51 by laskolin          #+#    #+#             */
/*   Updated: 2020/07/16 17:39:26 by laskolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	move_dude(t_wolf *wo, int n)
{
	if (wo->world == 1 && (wo->ray->deg > 0.0 && wo->ray->deg < 270.0))
		mlx_put_image_to_window(wo->mlx, wo->win, wo->moon.img,
			PLANE_W + 40 - wo->ray->deg * 6, 20);
	if (wo->fooot >= 1.0)
	{
		if (n == 1)
			mlx_put_image_to_window(wo->mlx, wo->win, wo->back.img,
				DUDE_XX, DUDE_YY);
		else if (n == 2)
			mlx_put_image_to_window(wo->mlx, wo->win, wo->dude.img,
				DUDE_XX, DUDE_YY);
	}
	else if (wo->fooot < 1.0)
	{
		if (n == 1)
			mlx_put_image_to_window(wo->mlx, wo->win, wo->back2.img,
				DUDE_XX, DUDE_YY);
		else if (n == 2)
			mlx_put_image_to_window(wo->mlx, wo->win, wo->dude2.img,
				DUDE_XX, DUDE_YY);
	}
	wo->fooot += 0.2;
	if (wo->fooot >= 2.0)
		wo->fooot = 0.0;
}

void	turn_left(t_wolf *wo)
{
	paint_plane(wo);
	if (wo->facing == 1)
	{
		wo->ray->deg += 4.0;
		if (wo->ray->deg == 360.0)
			wo->ray->deg = 0.0;
		move_dude(wo, 2);
	}
	else
	{
		wo->ray->deg -= 4.0;
		if (wo->ray->deg < 0.0)
			wo->ray->deg = 360.0 - fabs(wo->ray->deg);
		move_dude(wo, 1);
	}
	wo->energy -= 0.1;
	raycast(wo, wo->ray);
	mlx_put_image_to_window(wo->mlx, wo->win, wo->plane, 20, PLANE_H / 4);
	energy(wo);
}

void	turn_right(t_wolf *wo)
{
	paint_plane(wo);
	if (wo->facing == 0)
	{
		wo->ray->deg += 4.0;
		if (wo->ray->deg > 360.0)
			wo->ray->deg = fabs(wo->ray->deg) - 360.0;
		move_dude(wo, 1);
	}
	else
	{
		wo->ray->deg -= 4.0;
		if (wo->ray->deg < 0.0)
			wo->ray->deg = 360.0 - fabs(wo->ray->deg);
		move_dude(wo, 2);
	}
	wo->energy -= 0.1;
	raycast(wo, wo->ray);
	mlx_put_image_to_window(wo->mlx, wo->win, wo->plane, 20, PLANE_H / 4);
	energy(wo);
}

void	walk(t_wolf *wo)
{
	int		try_x;
	int		try_y;
	int		xmove;
	int		ymove;

	wo->facing = 0;
	xmove = cos((wo->ray->deg + FOV / 2) * M_PI / 180) * 200;
	wo->closex = cos((wo->ray->deg + FOV / 2) * M_PI / 180) * 600;
	ymove = sin((wo->ray->deg + FOV / 2) * M_PI / 180) * 200;
	wo->closey = sin((wo->ray->deg + FOV / 2) * M_PI / 180) * 600;
	try_x = (wo->ray->dude_x - wo->closex) / SIZE;
	try_y = (wo->ray->dude_y - wo->closey) / SIZE;
	if (wo->maze[try_y * wo->maze_w + try_x] != 1 && try_x >= 0 &&
		try_x < wo->maze_w && try_y >= 0 && try_y < wo->maze_h &&
			not_corner(try_x, try_y, wo) == 1)
		go(xmove, ymove, wo);
	else
		bounce_wall(wo);
	move_dude(wo, 1);
	energy(wo);
	if (wo->maze[try_y * wo->maze_w + try_x] == 8)
		lights_out(wo);
}

void	walk_back(t_wolf *wo)
{
	int		try_x;
	int		try_y;
	int		newspot;
	int		xmove;
	int		ymove;

	xmove = cos((wo->ray->deg + FOV / 2) * M_PI / 180) * 200;
	ymove = sin((wo->ray->deg + FOV / 2) * M_PI / 180) * 200;
	try_x = (wo->ray->dude_x + xmove) / SIZE;
	try_y = (wo->ray->dude_y + ymove) / SIZE;
	newspot = try_y * wo->maze_w + try_x;
	if (wo->maze[newspot] != 1 && try_x >= 0 && try_x < wo->maze_w &&
		try_y >= 0 && try_y < wo->maze_h && not_corner(try_x, try_y, wo) == 1)
	{
		wo->ray->dude_x += xmove;
		wo->ray->dude_y += ymove;
		paint_plane(wo);
		raycast(wo, wo->ray);
		mlx_put_image_to_window(wo->mlx, wo->win, wo->plane, 20, PLANE_H / 4);
	}
	wo->facing = 1;
	move_dude(wo, 2);
	energy(wo);
	if (wo->maze[newspot] == 8)
		lights_out(wo);
}
