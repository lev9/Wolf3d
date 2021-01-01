/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laskolin <laskolin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 09:06:51 by laskolin          #+#    #+#             */
/*   Updated: 2020/07/16 17:39:26 by laskolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	meazure_a_step(int x, int y, double alpha, t_ray *ray)
{
	if (alpha > 180.0 * M_PI / 180 && alpha < 360.0 * M_PI / 180)
	{
		ray->a_newy = (int)(y / SIZE) * SIZE + SIZE;
		ray->a_newx = (x - (ray->a_newy - y) /
			tan((360 * M_PI / 180 - alpha)));
		ray->a_stepy = SIZE;
		ray->a_stepx = SIZE / tan(alpha);
	}
	else
	{
		ray->a_newy = (int)(y / SIZE) * (SIZE) - 1;
		ray->a_newx = x - (ray->a_newy - y) /
			tan((180 * M_PI / 180 - alpha));
		ray->a_stepy = -SIZE;
		ray->a_stepx = -SIZE / tan(alpha);
	}
}

void	meazure_b_step(int x, int y, double alpha, t_ray *ray)
{
	if (alpha >= 90.0 * M_PI / 180 && alpha <= 270.0 * M_PI / 180)
	{
		ray->b_newx = (int)(x / SIZE) * SIZE + SIZE;
		if (alpha > 180 * M_PI / 180 && alpha < 360 * M_PI / 180)
			ray->b_newy = y + (x - ray->b_newx) *
				tan(360 * M_PI / 180 - alpha);
		else
			ray->b_newy = y + (x - ray->b_newx) *
				tan((180 * M_PI / 180 - alpha));
		ray->b_stepx = SIZE;
		ray->b_stepy = SIZE * tan(alpha);
	}
	else
	{
		ray->b_newx = (int)(x / SIZE) * SIZE - 1;
		if (alpha > 180 * M_PI / 180 && alpha < 360 * M_PI / 180)
			ray->b_newy = y + (x - ray->b_newx) *
				tan(360 * M_PI / 180 - alpha);
		else
			ray->b_newy = y + (x - ray->b_newx) *
				tan(180 * M_PI / 180 - alpha);
		ray->b_stepx = -SIZE;
		ray->b_stepy = -SIZE * tan(alpha);
	}
}

void	enemy_check(int x, int y, double alpha, t_wolf *wo)
{
	double test;

	test = 0.0;
	if (x == 0)
	{
		if (wo->ray->enemy_found == 0 && wo->maze[(int)wo->ray->a_point] == 5)
			wo->ray->enempd = (y - wo->ray->a_newy) / sin(alpha);
	}
	else
	{
		if (wo->ray->enemy_found == 0 && wo->maze[(int)wo->ray->b_point] == 5)
		{
			test = (x - wo->ray->b_newx) / cos(alpha);
			if (wo->ray->enempd == 0 || (test > 0 && test < wo->ray->enempd))
				wo->ray->enempd = test;
		}
	}
}

int		ray_a(int y, double alpha, t_wolf *wo, int obj)
{
	int		i;

	i = 0;
	while (i < 10000)
	{
		wo->ray->mazex = wo->ray->a_newx / SIZE;
		wo->ray->mazey = wo->ray->a_newy / SIZE;
		if (wo->ray->mazex < 0 || wo->ray->mazex > wo->maze_w - 1 ||
			wo->ray->mazey < 0 || wo->ray->mazey > wo->maze_h - 1)
			return (0);
		wo->ray->a_point = wo->ray->mazey * wo->maze_w + wo->ray->mazex;
		if (wo->maze[wo->ray->a_point] == obj ||
			(obj == 1 && wo->maze[wo->ray->a_point] == 8))
		{
			wo->ray->a_pd = (y - wo->ray->a_newy) / sin(alpha);
			return (1);
		}
		if (wo->maze[(int)wo->ray->a_point] == 9)
			wo->doors = 1;
		enemy_check(0, y, alpha, wo);
		i++;
		wo->ray->a_newx += wo->ray->a_stepx;
		wo->ray->a_newy += wo->ray->a_stepy;
	}
	return (0);
}

int		ray_b(int x, double alpha, t_wolf *wo, int obj)
{
	int		i;

	i = 0;
	while (i < 10000)
	{
		wo->ray->mazex = wo->ray->b_newx / SIZE;
		wo->ray->mazey = wo->ray->b_newy / SIZE;
		if (wo->ray->mazex < 0 || wo->ray->mazex > wo->maze_w - 1 ||
			wo->ray->mazey < 0 || wo->ray->mazey > wo->maze_h - 1)
			return (0);
		wo->ray->b_point = wo->ray->mazey * wo->maze_w + wo->ray->mazex;
		if (wo->maze[wo->ray->b_point] == obj ||
			(obj == 1 && wo->maze[wo->ray->b_point] == 8))
		{
			wo->ray->b_pd = fabs((x - wo->ray->b_newx) / cos(alpha));
			return (1);
		}
		if (wo->maze[(int)wo->ray->b_point] == 9)
			wo->doors = 1;
		enemy_check(x, 0, alpha, wo);
		i++;
		wo->ray->b_newx += wo->ray->b_stepx;
		wo->ray->b_newy += wo->ray->b_stepy;
	}
	return (0);
}
