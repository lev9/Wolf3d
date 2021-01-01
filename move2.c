/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laskolin <laskolin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 09:06:51 by laskolin          #+#    #+#             */
/*   Updated: 2020/07/16 17:39:26 by laskolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	go(int xmove, int ymove, t_wolf *wo)
{
	wo->ray->dude_x -= xmove;
	wo->ray->dude_y -= ymove;
	paint_plane(wo);
	raycast(wo, wo->ray);
	wo->energy -= 0.1;
	mlx_put_image_to_window(wo->mlx, wo->win, wo->plane, 20, PLANE_H / 4);
}

void	bounce_wall(t_wolf *wo)
{
	double	d;
	int		dudespot;

	d = wo->ray->deg + 30;
	if (d >= 360.0)
		d -= 360;
	dudespot = (int)wo->ray->dude_y / SIZE * wo->maze_w +
		(int)wo->ray->dude_x / SIZE;
	if (d > 0.0 && d < 90.0 && wo->maze[dudespot - 1] != 0)
		wo->ray->deg += 10;
	else if (d >= 0.0 && d < 90.0 && wo->maze[dudespot - wo->maze_w] != 0)
		wo->ray->deg -= 10;
	else if (d >= 90.0 && d < 180.0 && wo->maze[dudespot - wo->maze_w] != 0)
		wo->ray->deg += 10;
	else if (d >= 90.0 && d < 180.0 && wo->maze[dudespot + 1] != 0)
		wo->ray->deg -= 10;
	else if (d >= 180.0 && d < 270.0 && wo->maze[dudespot + 1] != 0)
		wo->ray->deg += 10;
	else if (d >= 180.0 && d < 270.0 && wo->maze[dudespot + wo->maze_w] != 0)
		wo->ray->deg -= 10;
	else if (d >= 270.0 && wo->maze[dudespot - 1] != 0)
		wo->ray->deg -= 10;
	else if (d >= 270.0 && wo->maze[dudespot + wo->maze_w] != 0)
		wo->ray->deg += 10;
	stay_round(wo);
}

int		not_corner(int try_x, int try_y, t_wolf *wo)
{
	int		x;
	int		y;
	int		dudespot;

	x = (int)wo->ray->dude_x / SIZE;
	y = (int)wo->ray->dude_y / SIZE;
	dudespot = y * wo->maze_w + x;
	if ((try_x < x && try_y < y && wo->maze[dudespot - 1] != 0 &&
		wo->maze[dudespot - wo->maze_w] != 0) || (try_x > x && try_y < y &&
		wo->maze[dudespot + 1] != 0 && wo->maze[dudespot - wo->maze_w] != 0) ||
		(try_x > x && try_y > y && wo->maze[dudespot + 1] != 0 &&
		wo->maze[dudespot + wo->maze_w] != 0) || (try_x < x && try_y > y &&
		wo->maze[dudespot - 1] != 0 && wo->maze[dudespot + wo->maze_w] != 0))
		return (0);
	return (1);
}

void	corner(int c, int wallnr, t_wolf *wo)
{
	int		i;

	i = 1;
	while (wo->pds[c - i] - wo->ray->pdpd > 20 && !(wo->pds[c - 5] -
		wo->ray->pdpd > 20))
	{
		draw_a_wall(c - i, wallnr, wo, wo->ray);
		wo->ray->pdpd -= 0.5;
		i++;
	}
}

void	fix_corner(int obj, int wallnr, int c, t_wolf *wo)
{
	int		i;

	if (obj == 9)
		wo->cols[c] = 9;
	else if (wo->pds[c] < 2000 && c > 3)
	{
		i = wo->cols[c - 1];
		if (i != 9 && wo->cols[c] != i && wo->cols[c] == wo->cols[c - 3])
		{
			wo->cols[c - 1] = wo->ray->col;
			wo->cols[c - 2] = wo->ray->col;
			draw_a_wall(c - 1, wallnr, wo, wo->ray);
			draw_a_wall(c - 2, wallnr, wo, wo->ray);
		}
	}
}
