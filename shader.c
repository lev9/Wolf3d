/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laskolin <laskolin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 09:06:51 by laskolin          #+#    #+#             */
/*   Updated: 2020/07/16 17:39:26 by laskolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		get_r(int n)
{
	int	r[14];

	r[0] = 0;
	r[1] = 169;
	r[2] = 168;
	r[3] = 99;
	r[4] = 57;
	r[5] = 64;
	r[6] = 201;
	r[7] = 189;
	r[8] = 151;
	r[9] = 247;
	r[13] = 255;
	if (n == 10)
		return (r[4]);
	return (r[n]);
}

int		get_g(int n)
{
	int	g[14];

	g[0] = 1;
	g[1] = 209;
	g[2] = 50;
	g[3] = 102;
	g[4] = 64;
	g[5] = 0;
	g[6] = 201;
	g[7] = 168;
	g[8] = 252;
	g[9] = 87;
	g[13] = 251;
	if (n == 10)
		return (g[4]);
	return (g[n]);
}

int		get_b(int n)
{
	int	b[14];

	b[0] = 74;
	b[1] = 142;
	b[2] = 50;
	b[3] = 99;
	b[4] = 20;
	b[5] = 0;
	b[6] = 201;
	b[7] = 134;
	b[8] = 220;
	b[9] = 87;
	b[13] = 130;
	if (n == 10)
		return (b[4]);
	return (b[n]);
}

int		shade(int n, double i)
{
	int		r;
	int		g;
	int		b;

	if (n == 4)
		return (0x000000);
	if (n == 11)
		return (0xe6ff00e6);
	if (n == 10)
		return (0xFFFFFF);
	if (n == 12)
		n = 4;
	r = get_r(n);
	g = get_g(n);
	b = get_b(n);
	if (i > 0 && i < 1)
	{
		r *= i;
		g *= i;
		b *= i;
	}
	return (int)(0 | (r << 16) | (g << 8) | b);
}

void	paint_floor(int col, int i, int c, t_wolf *wo)
{
	while (i < PLANE_H)
	{
		wo->planebuf[i * PLANE_W + c] = shade(col, 200.0 / (800 - i));
		i++;
	}
}
