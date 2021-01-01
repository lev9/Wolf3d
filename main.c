/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laskolin <laskolin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 09:06:51 by laskolin          #+#    #+#             */
/*   Updated: 2020/07/16 17:39:26 by laskolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		end(t_wolf *wo)
{
	free(wo->mlx);
	exit(0);
}

int		exit_hook(t_wolf *wo)
{
	free(wo->mlx);
	exit(0);
}

int		errormessage(int error)
{
	write(1, "========================================\n", 41);
	if (error == 1)
		write(1, "Give 1 maze as a parameter\n", 27);
	if (error == 2)
		write(1, "Error reading file\n", 19);
	if (error == 3)
		write(1, "Map can contain 0, 1, 5, 6, 8, 9\n", 33);
	if (error == 4)
		write(1, "Too many players on map\n", 24);
	if (error == 5)
		write(1, "Map lines must be equally long\n", 31);
	if (error == 6)
	{
		write(1, "Map must be a rectangle with 1's ", 34);
		write(1, "as borders and 0's as floor\n", 28);
	}
	if (error == 8)
		write(1, "Map width must be 8 - 10000\n", 28);
	if (error == 10)
		write(1, "Given argument is a directory\n", 30);
	write(1, "========================================\n", 41);
	exit(0);
}

int		main(int argc, char **argv)
{
	t_wolf	newwolf;
	t_wolf	*wo;
	t_ray	newray;

	if (argc != 2)
		return (errormessage(1));
	if (open(argv[1], O_DIRECTORY) != -1)
		return (errormessage(10));
	wo = &newwolf;
	wo->mlx = mlx_init();
	wo->win = mlx_new_window(wo->mlx, 960 + 40, 600 * 1.5, "WOLF3D");
	wo->ray = &newray;
	wo->mazename = argv[1];
	get_maze(argv[1], wo);
	get_images(wo);
	free(wo->maze);
	get_maze("mazes/maze1.wolf", wo);
	instructions("manual.txt");
	start_screen(wo);
	mlx_hook(wo->win, 2, 1L << 0, deal_key, wo);
	mlx_hook(wo->win, 17, 0, exit_hook, wo);
	mlx_loop(wo->mlx);
	return (0);
}
