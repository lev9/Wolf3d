/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laskolin <laskolin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 09:06:51 by laskolin          #+#    #+#             */
/*   Updated: 2020/07/16 17:39:26 by laskolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		draw_enemy(int i, double yy, double xjump, t_wolf *wo)
{
	double	xx;
	int		h;
	int		col;
	int		xspot;

	if (wo->ray->slice_y + i >= 0 && (int)(wo->ray->slice_y + i) < PLANE_H)
	{
		xx = 0;
		h = 0;
		while (h < wo->ray->slice_h)
		{
			xspot = wo->ray->enemy_c + h;
			if (xspot >= 0 && xspot < PLANE_W && wo->ray->enempd
				< wo->pds[xspot])
			{
				col = wo->enembuf.buf[(int)((int)(yy) * 63 + (int)xx)];
				if (col != 0x5a5b99)
					wo->planebuf[(int)((int)(wo->ray->slice_y) +
						i - 1) * PLANE_W + xspot] = col;
			}
			h++;
			xx += xjump;
		}
	}
}

void		enemy(t_wolf *wo, t_ray *ray)
{
	double	jump;
	double	xjump;
	double	yy;
	int		i;

	ray->slice_h = (SIZE / ray->enempd) * ray->distance;
	if (ray->enemy_c >= 0 && ray->enempd < wo->pds[ray->enemy_c])
	{
		ray->slice_y = PLANE_H / ray->look - (ray->slice_h / wo->tiny);
		i = 0;
		yy = 0;
		jump = 65 / (double)ray->slice_h;
		xjump = 63 / (double)ray->slice_h;
		while (i < ray->slice_h)
		{
			draw_enemy(i, yy, xjump, wo);
			i++;
			yy += jump;
		}
	}
	else
		ray->enempd = 0;
}

int			choose_wall(t_ray *ray)
{
	if (ray->col == 1)
		return (0);
	if (ray->col == 2)
		return (4);
	if (ray->col == 3)
		return (2);
	else
		return (12);
}

t_wimage	door(t_wolf *wo)
{
	t_wimage		d[15];

	d[0] = wo->d2buf;
	d[1] = wo->d3buf;
	d[1] = wo->d4buf;
	d[2] = wo->d5buf;
	d[3] = wo->d6buf;
	d[4] = wo->d7buf;
	d[5] = wo->d8buf;
	d[6] = wo->d9buf;
	d[7] = wo->d10buf;
	d[8] = wo->d11buf;
	d[9] = wo->d12buf;
	d[10] = wo->d13buf;
	d[11] = wo->d14buf;
	d[12] = wo->d15buf;
	d[13] = wo->d16buf;
	d[14] = wo->d17buf;
	if (wo->curdoor == 0)
		wo->curdoor = wo->ray->pdpd / 250;
	if (wo->curdoor > 13)
		return (d[14]);
	return (d[wo->curdoor]);
}

t_wimage	choose_wimage(int wallnr, t_wolf *wo, t_ray *ray)
{
	t_wimage		wimg;

	if (wallnr == 1)
	{
		if (ray->col == 1)
			wimg = wo->wallbuf;
		if (ray->col == 3)
		{
			if (wo->facing == 1)
				return (wo->digibuf);
			return (wo->digi2buf);
		}
		if (ray->col == 2)
		{
			if (ray->mazey % 2 == 0)
				wimg = wo->logo1buf;
			else
				wimg = wo->logo2buf;
		}
		if (ray->col == 4)
			wimg = wo->bwbuf;
	}
	else
		wimg = door(wo);
	return (wimg);
}
