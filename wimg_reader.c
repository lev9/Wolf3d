/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wimgreader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laskolin <laskolin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 09:06:51 by laskolin          #+#    #+#             */
/*   Updated: 2020/07/16 17:39:26 by laskolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			*new_arr(int size)
{
	int			*arr;

	arr = (int*)malloc(size * sizeof(int));
	return (arr);
}

int			*fill_wimage_buf2(char *str, t_wimage wimg, char *name, int done)
{
	int			*buf;
	int			i;

	buf = new_arr(wimg.width * wimg.height);
	i = 0;
	while (str[i] != '\0')
	{
		if (done == 0 && str[i] != ' ')
			buf[i] = img_color(name, str[i] - '0');
		else if (str[i] == ' ')
			buf[i] = buf[i - 1];
		else
			buf[i] = str[i] - '0';
		i++;
	}
	return (buf);
}

t_wimage	new_wimage(char *name, int done)
{
	t_wimage	wimg;
	int			fd;
	char		*line;
	char		*str;
	char		*swap;

	wimg.height = 0;
	fd = open(name, O_RDONLY);
	check_fd(fd);
	str = ft_strnew(0);
	while (get_next_line(fd, &line))
	{
		if (wimg.height == 0)
			wimg.width = ft_strlen(line);
		swap = ft_strjoin(str, line);
		free(str);
		free(line);
		str = swap;
		wimg.height++;
	}
	wimg.buf = fill_wimage_buf2(str, wimg, name, done);
	close(fd);
	free(str);
	return (wimg);
}

void		get_arrays2(t_wolf *wo)
{
	wo->d14buf = new_wimage("images/door/door14", 1);
	wo->d15buf = new_wimage("images/door/door15", 1);
	wo->d16buf = new_wimage("images/door/door16", 1);
	wo->d17buf = new_wimage("images/door/door17", 1);
	wo->wallbuf = new_wimage("images/wall.wolf", 0);
	wo->logo1buf = new_wimage("images/walllogo1.wolf", 0);
	wo->logo2buf = new_wimage("images/walllogo2.wolf", 0);
	wo->bwbuf = new_wimage("images/bw_wall.wolf", 1);
	wo->enembuf = new_wimage("images/enem.wolf", 0);
}

void		get_arrays(t_wolf *wo)
{
	wo->d2buf = new_wimage("images/door/door2", 1);
	wo->d3buf = new_wimage("images/door/door3", 1);
	wo->d4buf = new_wimage("images/door/door4", 1);
	wo->d5buf = new_wimage("images/door/door5", 1);
	wo->d6buf = new_wimage("images/door/door6", 1);
	wo->d7buf = new_wimage("images/door/door7", 1);
	wo->d8buf = new_wimage("images/door/door8", 1);
	wo->d9buf = new_wimage("images/door/door9", 1);
	wo->d10buf = new_wimage("images/door/door10", 1);
	wo->d11buf = new_wimage("images/door/door11", 1);
	wo->d12buf = new_wimage("images/door/door12", 1);
	wo->d13buf = new_wimage("images/door/door13", 1);
	get_arrays2(wo);
}
