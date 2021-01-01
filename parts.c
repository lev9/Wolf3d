/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parts.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laskolin <laskolin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 09:06:51 by laskolin          #+#    #+#             */
/*   Updated: 2020/07/16 17:39:26 by laskolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	start_values(t_wolf *wo, t_ray *ray)
{
	ray->deg = 75.00;
	ray->distance = (PLANE_W / 2) / tan((FOV / 2) * M_PI / 180);
	wo->world = 1;
	wo->score = 0;
	wo->energy = 10;
	wo->lives = 3;
	wo->middle = 0;
	wo->started = 0;
	wo->fooot = 0.0;
	wo->facing = 0;
	wo->gotlife = 0;
	wo->tiny = 2;
	if (wo->pds == NULL)
		wo->pds = new_arr(PLANE_W);
	if (wo->cols == NULL)
		wo->cols = new_arr(PLANE_W);
	ray->look = 2.0;
}

void	start_screen(t_wolf *wo)
{
	start_values(wo, wo->ray);
	raycast(wo, wo->ray);
	mlx_put_image_to_window(wo->mlx, wo->win, wo->start.img,
		PLANE_W / 2 - 50, PLANE_H / 2 - 30);
	mlx_put_image_to_window(wo->mlx, wo->win, wo->moon.img,
		PLANE_W + 40 - wo->ray->deg * 6, 20);
	mlx_string_put(wo->mlx, wo->win, PLANE_W / 2 - 185, PLANE_H / 2 + 100,
		0xFFFFFF, "P R E S S   S P A C E   T O   S T A R T");
	mlx_string_put(wo->mlx, wo->win, PLANE_W / 2 - 186, PLANE_H / 2 + 100,
		0xFFFFFF, "P R E S S   S P A C E   T O   S T A R T");
}

void	continue_screen(t_wolf *wo)
{
	mlx_clear_window(wo->mlx, wo->win);
	start_values(wo, wo->ray);
	free(wo->maze);
	get_maze("mazes/maze1.wolf", wo);
	paint_plane(wo);
	raycast(wo, wo->ray);
	mlx_put_image_to_window(wo->mlx, wo->win, wo->moon.img,
		PLANE_W + 40 - wo->ray->deg * 6, 20);
	mlx_put_image_to_window(wo->mlx, wo->win, wo->plane, 20, PLANE_H / 4);
	mlx_put_image_to_window(wo->mlx, wo->win, wo->ban.img, BAN_X, BAN_Y);
	energy(wo);
	mlx_put_image_to_window(wo->mlx, wo->win, wo->dude.img, DUDE_XX, DUDE_YY);
	mlx_put_image_to_window(wo->mlx, wo->win, wo->start.img,
		PLANE_W / 2 - 50, PLANE_H / 2 - 30);
	print_stats(wo);
	wo->started = 1;
	wo->lights = 1;
}

void	change_world(t_wolf *wo)
{
	wo->ray->deg = 75.00;
	mlx_clear_window(wo->mlx, wo->win);
	wo->world++;
	free(wo->maze);
	if (wo->world == 4)
		wo->world = 1;
	if (wo->world == 1)
	{
		get_maze("mazes/maze1.wolf", wo);
		mlx_put_image_to_window(wo->mlx, wo->win, wo->moon.img,
			PLANE_W + 40 - wo->ray->deg * 6, 20);
	}
	else if (wo->world == 2)
		get_maze("mazes/maze2.wolf", wo);
	else if (wo->world == 3)
		get_maze(wo->mazename, wo);
	wo->ray->look = 2.0;
	paint_plane(wo);
	raycast(wo, wo->ray);
	mlx_put_image_to_window(wo->mlx, wo->win, wo->plane, 20, PLANE_H / 4);
	wo->lights = 1;
}

void	lights_out(t_wolf *wo)
{
	int		i;
	int		col;

	i = 0;
	while (i < PLANE_W * PLANE_H)
	{
		col = wo->planebuf[i];
		col = (col & 0xfefefe) >> 1;
		col = (col & 0xfefefe) >> 1;
		wo->planebuf[i] = col;
		i++;
	}
	wo->lights = 0;
	mlx_clear_window(wo->mlx, wo->win);
	mlx_put_image_to_window(wo->mlx, wo->win, wo->plane, 20, PLANE_H / 4);
	if (wo->world == 3)
		mlx_string_put(wo->mlx, wo->win, (PLANE_W + 40) / 2 - 220, PLANE_H *
		0.50 + 65, 0x00FF00, "YOU'RE TRAVELING BACK IN TIME NOW...PRESS X");
	else
		mlx_string_put(wo->mlx, wo->win, (PLANE_W + 40) / 2 - 160, PLANE_H *
		0.50 + 65, 0xFFFFFF, "YOU SOLVED THE WORLD.....PRESS X");
	mlx_put_image_to_window(wo->mlx, wo->win, wo->start.img,
		PLANE_W / 2 - 50, PLANE_H / 2 - 30);
}
