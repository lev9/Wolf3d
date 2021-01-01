/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laskolin <laskolin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 09:06:51 by laskolin          #+#    #+#             */
/*   Updated: 2020/07/16 17:39:26 by laskolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	fix_ray(t_wolf *wo, t_ray *ray, double alpha)
{
	if (ray->col == 2)
	{
		if (wo->maze[(int)ray->pointpoint - 1] == 1)
			ray->col = 1;
	}
	else if (ray->col == 1)
	{
		if (wo->maze[(int)ray->pointpoint + wo->maze_w] == 1)
			ray->col = 4;
	}
	else if (ray->col == 3)
	{
		if (wo->maze[(int)ray->pointpoint - wo->maze_w] == 1)
			ray->col = 4;
	}
	else if (ray->col == 4)
	{
		if (wo->maze[(int)ray->pointpoint + 1] == 1 ||
		(alpha > 90 && alpha < 270))
			ray->col = 1;
	}
	if (wo->ray->col == 2 || wo->ray->col == 4)
		wo->ray->offset = (int)wo->ray->b_newy % (int)SIZE;
	else if (wo->ray->col == 1 || wo->ray->col == 3)
		wo->ray->offset = (int)wo->ray->a_newx % (int)SIZE;
}

void	choose_a_or_b(int a, int b, double alpha, t_wolf *wo)
{
	if ((b == 0 && a == 1) || (b == 1 && a == 1 &&
		wo->ray->a_pd < wo->ray->b_pd))
	{
		wo->ray->pointpoint = wo->ray->a_point;
		wo->ray->pdpd = wo->ray->a_pd;
		if (alpha >= 0.0 * M_PI / 180 && alpha <= 180.0 * M_PI / 180)
			wo->ray->col = 1;
		else if (alpha > 180.0 * M_PI / 180 && alpha <= 360.0 * M_PI / 180)
			wo->ray->col = 3;
	}
	if ((a == 0 && b == 1) || (b == 1 && a == 1 &&
		wo->ray->b_pd < wo->ray->a_pd))
	{
		wo->ray->pointpoint = wo->ray->b_point;
		wo->ray->pdpd = wo->ray->b_pd;
		if (alpha > 90.0 * M_PI / 180 && alpha <= 270.0 * M_PI / 180)
			wo->ray->col = 2;
		else if (alpha > 270.0 * M_PI / 180 || alpha <= 90.0 * M_PI / 180)
			wo->ray->col = 4;
	}
	fix_ray(wo, wo->ray, alpha);
}

void	doors_and_enemies(int c, double alpha, t_wolf *wo, t_ray *ray)
{
	double beta;

	if (wo->doors == 1)
	{
		wo->ray->pdpd = 0;
		wo->ray->a_pd = 0;
		wo->ray->b_pd = 0;
		rays(wo, c, alpha, 9);
	}
	if (ray->enemy_found == 0 && ray->enempd > 0)
	{
		beta = -30.0 * M_PI / 180 + c * (FOV * M_PI / 180 / PLANE_W);
		ray->enempd = ray->enempd * cos(beta);
		ray->enemy_c = c;
		ray->enemy_found = 1;
	}
}

void	rays(t_wolf *wo, int c, double alpha, int obj)
{
	int		a;
	int		b;
	int		wallnr;

	meazure_a_step(wo->ray->dude_x, wo->ray->dude_y, alpha, wo->ray);
	a = ray_a(wo->ray->dude_y, alpha, wo, obj);
	meazure_b_step(wo->ray->dude_x, wo->ray->dude_y, alpha, wo->ray);
	if ((wo->ray->b_newy > 0))
		b = ray_b(wo->ray->dude_x, alpha, wo, obj);
	else
		b = 0;
	choose_a_or_b(a, b, alpha, wo);
	wo->cols[c] = wo->ray->col;
	wo->ray->pdpd *= cos(-30.0 * M_PI / 180 + c * (FOV * M_PI / 180 / PLANE_W));
	wallnr = wo->maze[(int)wo->ray->pointpoint];
	if (!(obj == 9 && wo->pds[c] < wo->ray->pdpd))
	{
		draw_a_wall(c, wallnr, wo, wo->ray);
		fix_corner(obj, wallnr, c, wo);
	}
	wo->pds[c] = (int)wo->ray->pdpd;
}

void	raycast(t_wolf *wo, t_ray *ray)
{
	double	alpha;
	int		c;

	wo->curdoor = 0;
	ray->enemy_found = 0;
	ray->enempd = 0;
	alpha = ray->deg * M_PI / 180;
	c = 0;
	while (c < PLANE_W)
	{
		wo->doors = 0;
		wo->ray->pdpd = 0;
		wo->ray->a_pd = 0;
		wo->ray->b_pd = 0;
		rays(wo, c, alpha, 1);
		doors_and_enemies(c, alpha, wo, ray);
		alpha += ((FOV * M_PI / 180 / PLANE_W));
		if (alpha > 360.0 * M_PI / 180)
			alpha -= (360.0 * M_PI / 180);
		if (alpha < 0.0 * M_PI / 180)
			alpha += (360.0 * M_PI / 180);
		c++;
	}
	if (ray->enemy_found == 1)
		enemy(wo, wo->ray);
}
