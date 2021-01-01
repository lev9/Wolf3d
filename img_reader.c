/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laskolin <laskolin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 09:06:51 by laskolin          #+#    #+#             */
/*   Updated: 2020/07/16 17:39:26 by laskolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			img_color(char *name, int n)
{
	if (ft_strcmp(name, "images/start.wolf") == 0 && n == 0)
		return (0xFFFFFF00);
	if (ft_strcmp(name, "images/start.wolf") == 0 && n != 0)
		return (0xFF0000);
	if (ft_strcmp(name, "images/moon.wolf") == 0 && n == 0)
		return (0x000000);
	if (ft_strcmp(name, "images/moon.wolf") == 0 && n != 0)
		return (0xffd1fd);
	if (ft_strncmp(name, "images/wall", 11) == 0)
	{
		if (n == 8)
			return (10);
		if (n == 4)
			return (13);
		if (n == 0)
			return (6);
		return (n);
	}
	if ((ft_strncmp(name, "images/ba", 9) == 0 ||
	ft_strncmp(name, "images/co", 9) == 0) && n == 1)
		n = 10;
	if ((ft_strncmp(name, "images/du", 9) == 0 && n == 5))
		return (0xd1ff29);
	return (col(n));
}

void		fill_image_buf(char *str, t_image img, char *filename)
{
	int	i;

	img.buf = (int *)mlx_get_data_addr(img.img, &img.bits, &img.pixels,
		&img.endian);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
			img.buf[i] = img_color(filename, str[i] - '0');
		else if (str[i] == ' ')
			img.buf[i] = img.buf[i - 1];
		i++;
	}
	img.pixels /= 4;
}

t_image		create_image(int *mlx, char *filename)
{
	t_image		img;
	int			fd;
	char		*line;
	char		*str;
	char		*swap;

	img.height = 0;
	str = ft_strnew(0);
	fd = open(filename, O_RDONLY);
	check_fd(fd);
	while (get_next_line(fd, &line))
	{
		if (img.height == 0)
			img.width = (int)ft_strlen(line);
		swap = ft_strjoin(str, line);
		free(str);
		free(line);
		str = swap;
		img.height++;
	}
	img.img = mlx_new_image(mlx, img.width, img.height);
	fill_image_buf(str, img, filename);
	close(fd);
	free(str);
	return (img);
}

t_image		create_xpm(int *mlx, char *filename)
{
	t_image		img;

	img.img = mlx_xpm_file_to_image(mlx, filename, &img.width, &img.height);
	img.buf = (int *)mlx_get_data_addr(img.img, &img.bits, &img.pixels,
		&img.endian);
	img.pixels /= 4;
	return (img);
}

void		get_images(t_wolf *wo)
{
	int			bits;
	int			pixels;
	int			endian;

	wo->plane = mlx_new_image(wo->mlx, 960, 600);
	wo->planebuf = (int*)mlx_get_data_addr(wo->plane, &bits, &pixels, &endian);
	wo->gray = create_xpm(wo->mlx, "images/graf.xpm");
	wo->start = create_image(wo->mlx, "images/start.wolf");
	wo->moon = create_image(wo->mlx, "images/moon.wolf");
	wo->dude = create_image(wo->mlx, "images/dudeb.wolf");
	wo->dude2 = create_image(wo->mlx, "images/dude2b.wolf");
	wo->back = create_image(wo->mlx, "images/dudeback.wolf");
	wo->back2 = create_image(wo->mlx, "images/dudeback2.wolf");
	wo->ban = create_image(wo->mlx, "images/ban.wolf");
	wo->ban2 = create_image(wo->mlx, "images/ban2.wolf");
	wo->north = create_image(wo->mlx, "images/north.wolf");
	wo->east = create_image(wo->mlx, "images/east.wolf");
	wo->south = create_image(wo->mlx, "images/south.wolf");
	wo->west = create_image(wo->mlx, "images/west.wolf");
	get_arrays(wo);
}
