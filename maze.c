/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maze.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laskolin <laskolin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 09:06:51 by laskolin          #+#    #+#             */
/*   Updated: 2020/07/16 17:39:26 by laskolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		instructions(char *file)
{
	char	*line;
	int		fd;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (errormessage(2));
	while (get_next_line(fd, &line))
	{
		i = 0;
		while (line[i] != '\0')
		{
			write(1, &line[i], 1);
			i++;
		}
		write(1, "\n", 1);
		free(line);
	}
	close(fd);
	return (0);
}

int		maze_to_digit(char *str, t_wolf *wo)
{
	int	len;
	int	i;
	int	n;

	len = ft_strlen(str);
	wo->maze = (int*)malloc(sizeof(int) * len);
	i = 0;
	while (i < len)
	{
		n = str[i] - '0';
		wo->maze[i] = n;
		if ((wo->startpoints == 0 && n == 0) || n == 6)
		{
			wo->ray->dude_y = (i / wo->maze_w * SIZE);
			wo->ray->dude_x = (i % wo->maze_w * SIZE);
		}
		i++;
	}
	return (0);
}

int		check_c(char c, int len, t_wolf *wo)
{
	if (c != '1')
	{
		wo->borders = 1;
		if (wo->maze_h == 0 || (wo->maze_h > 0 &&
			(len == 0 || len == wo->maze_w - 1)))
			return (errormessage(6));
	}
	if (c == '6')
		wo->startpoints++;
	if (wo->startpoints > 1)
		return (errormessage(4));
	if (c == '0')
		wo->valid_zero++;
	if (c != '0' && c != '1' && c != '5' && c != '6' && c != '8' && c != '9')
		return (errormessage(3));
	return (0);
}

int		check_line(char *line, t_wolf *wo)
{
	int		len;
	char	c;

	len = 0;
	wo->borders = 0;
	while (line[len] != '\0')
	{
		c = line[len];
		check_c(c, len, wo);
		len++;
	}
	if (wo->maze_h == 0)
	{
		wo->maze_w = len;
		if (wo->maze_w > 10000 || wo->maze_w < 8)
			return (errormessage(8));
	}
	if (wo->maze_h > 0 && len != wo->maze_w)
		return (errormessage(5));
	free(line);
	wo->maze_h++;
	if (wo->maze_h > 10000)
		return (errormessage(8));
	return (0);
}

int		get_maze(char *name, t_wolf *wo)
{
	char	*line;
	char	*str;
	int		fd;
	char	*swap;

	wo->startpoints = 0;
	wo->valid_zero = 0;
	wo->maze_h = 0;
	wo->maze_w = 0;
	fd = open(name, O_RDONLY);
	check_fd(fd);
	str = ft_strnew(0);
	while (get_next_line(fd, &line))
	{
		check_line(line, wo);
		swap = ft_strjoin(str, line);
		free(str);
		str = swap;
	}
	if (wo->borders == 1 || wo->valid_zero == 0)
		return (errormessage(6));
	maze_to_digit(str, wo);
	free(str);
	close(fd);
	return (0);
}
