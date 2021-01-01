/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laskolin <laskolin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 09:06:51 by laskolin          #+#    #+#             */
/*   Updated: 2020/07/16 17:39:26 by laskolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_greenwalls(int c, t_ray *ray, t_wolf *wo)
{
	int			i;
	int			color;
	int			shade;

	i = ray->slice_y - 60;
	color = 0;
	shade = ray->pdpd / 64.0;
	while (i < ray->slice_y + ray->slice_h + 40 && i < PLANE_H)
	{
		if (i >= 0)
		{
			if (i == (ray->slice_y + ray->slice_h + 40) - 62)
				color = 61;
			wo->planebuf[i * PLANE_W + c] = greenwalls((color - shade) / 10);
			if (i == (ray->slice_y + ray->slice_h + 40) - 63)
			{
				if (c % 20 == 0)
					wo->planebuf[i * PLANE_W + c] = 0x00FF00;
				break ;
			}
		}
		i++;
		color += 1;
	}
}

void	draw_quattro(int c, t_wolf *wo, t_ray *ray)
{
	int			i;
	int			n;
	int			col;

	i = ray->slice_y;
	while (i < ray->slice_y + ray->slice_h)
	{
		if (i >= 0 && i * PLANE_W + c < PLANE_H * PLANE_W)
		{
			n = choose_wall(ray);
			col = shade(n, 1000 / ray->pdpd);
			wo->planebuf[i * PLANE_W + c] = col;
		}
		i++;
	}
}

void	draw_wimage(int c, int wallnr, t_wimage wimg, t_wolf *wo)
{
	int			i;
	int			cur;
	double		wall_y;
	double		jump;

	wall_y = 0.0;
	jump = (wimg.height - 1) / (double)wo->ray->slice_h;
	i = wo->ray->slice_y;
	while (i < wo->ray->slice_y + wo->ray->slice_h && i < PLANE_H)
	{
		if (i >= 0)
		{
			cur = 11;
			if (wallnr != 8)
				cur = wimg.buf[(int)wall_y * 64 + wo->ray->offset /
					(SIZE / wimg.width)];
			if (cur != 0)
				wo->planebuf[i * PLANE_W + c] =
				shade(cur, 3000 / wo->ray->pdpd);
		}
		wall_y += jump;
		i++;
	}
	if (wo->world == 3)
		paint_floor(1, i, c, wo);
}

void	draw_xpm(int c, int wallnr, t_image xpm, t_wolf *wo)
{
	int			i;
	int			cur;
	double		wall_y;
	double		jump;

	wall_y = 0.0;
	jump = xpm.height / (double)wo->ray->slice_h;
	i = wo->ray->slice_y;
	while (i < wo->ray->slice_y + wo->ray->slice_h && i < PLANE_H)
	{
		if (i >= 0)
		{
			if (wallnr == 8)
				cur = 0xe6ff00e6;
			else
				cur = xpm.buf[(int)wall_y * xpm.width +
		(int)((double)wo->ray->offset / ((double)SIZE / (double)xpm.width))];
			wo->planebuf[i * PLANE_W + c] = cur;
		}
		wall_y += jump;
		i++;
	}
	if (wo->world == 3)
		paint_floor(1, i, c, wo);
}

void	draw_a_wall(int c, int wallnr, t_wolf *wo, t_ray *ray)
{
	t_wimage	wimg;

	ray->slice_h = (SIZE / ray->pdpd) * ray->distance;
	ray->slice_y = PLANE_H / ray->look - (ray->slice_h / wo->tiny);
	if (wallnr == 8 || (wallnr == 9 && wo->world == 2) ||
	((wallnr == 1 || wallnr == 9) && wo->world == 3))
	{
		if (ray->col == 3 && wallnr != 9)
			draw_xpm(c, wallnr, wo->gray, wo);
		else
		{
			wimg = choose_wimage(wallnr, wo, ray);
			draw_wimage(c, wallnr, wimg, wo);
		}
	}
	else if (wo->world == 1)
		draw_greenwalls(c, ray, wo);
	else
		draw_quattro(c, wo, ray);
	if (wo->pds[c - 1] - wo->ray->pdpd > 20 && wo->doors == 0)
		corner(c, wallnr, wo);
	if (c == PLANE_W / 2)
		wo->middle = wo->ray->pointpoint;
}
