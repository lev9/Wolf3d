/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laskolin <laskolin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 08:41:17 by laskolin          #+#    #+#             */
/*   Updated: 2020/03/12 12:10:59 by laskolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# define PLANE_W 960
# define PLANE_H 600
# define SIZE 640
# define FOV 60
# define DUDE_H 64
# define DUDE_XX 468
# define DUDE_YY 750
# define BAN_X 318
# define BAN_Y 750
# define BAN2_X 556
# define BAN2_Y 750
# define _USE_MATH_DEFINES

# include "lib/libft/libft.h"
# include "lib/libmlx/mlx.h"
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>

typedef struct		s_image
{
	void	*img;
	int		*buf;
	int		bits;
	int		width;
	int		height;
	int		pixels;
	int		endian;
}					t_image;

typedef struct		s_wimage
{
	int		width;
	int		height;
	int		*buf;
}					t_wimage;

typedef struct		s_ray
{
	double	deg;
	double	dude_x;
	double	dude_y;
	int		mazex;
	int		mazey;
	double	a_stepx;
	double	a_stepy;
	double	a_newx;
	double	a_newy;
	int		a_point;
	double	a_pd;
	double	b_stepx;
	double	b_stepy;
	double	b_newx;
	double	b_newy;
	int		b_point;
	double	b_pd;
	double	pointpoint;
	double	pdpd;
	double	distance;
	int		slice_h;
	double	slice_y;
	int		offset;
	int		col;
	double	look;
	double	enempd;
	int		enemy_c;
	int		enemy_found;
}					t_ray;

typedef struct		s_wolf
{
	void		*mlx;
	void		*win;
	t_ray		*ray;
	void		*plane;
	int			*planebuf;
	t_image		gray;
	t_image		moon;
	t_image		dude;
	t_image		dude2;
	t_image		back;
	t_image		back2;
	t_image		ban;
	t_image		ban2;
	t_image		north;
	t_image		east;
	t_image		south;
	t_image		west;
	t_image		start;
	t_wimage	enembuf;
	t_wimage	digibuf;
	t_wimage	digi2buf;
	t_wimage	wallbuf;
	t_wimage	logo1buf;
	t_wimage	logo2buf;
	t_wimage	bwbuf;
	t_wimage	d2buf;
	t_wimage	d3buf;
	t_wimage	d4buf;
	t_wimage	d5buf;
	t_wimage	d6buf;
	t_wimage	d7buf;
	t_wimage	d8buf;
	t_wimage	d9buf;
	t_wimage	d10buf;
	t_wimage	d11buf;
	t_wimage	d12buf;
	t_wimage	d13buf;
	t_wimage	d14buf;
	t_wimage	d15buf;
	t_wimage	d16buf;
	t_wimage	d17buf;
	char		*mazename;
	int			*maze;
	int			maze_w;
	int			maze_h;
	int			valid_zero;
	int			borders;
	int			startpoints;
	int			world;
	int			score;
	int			lives;
	double		energy;
	double		fooot;
	int			facing;
	int			middle;
	int			started;
	int			gotlife;
	int			doors;
	int			curdoor;
	int			lights;
	int			tiny;
	int			*pds;
	int			*cols;
	int			closex;
	int			closey;
}					t_wolf;

/*
**	main.c
*/
int					end(t_wolf *wo);
int					exit_hook(t_wolf *wo);
int					errormessage(int error);
int					main(int argc, char **argv);

/*
**	parts.c
*/
void				start_values(t_wolf *wo, t_ray *ray);
void				start_screen(t_wolf *wo);
void				continue_screen(t_wolf *wo);
void				change_world(t_wolf *wo);
void				lights_out(t_wolf *wo);

/*
**      help.c
*/
void				print_stats(t_wolf *wo);
void				print_energy(t_wolf *wo);
void				compass(t_wolf *wo);
void				paint_plane(t_wolf *wo);
int					check_fd(int fd);

/*
**	maze.c
*/
int					instructions(char *file);
int					maze_to_digit(char *str, t_wolf *wo);
int					check_c(char c, int len, t_wolf *wo);
int					check_line(char *line, t_wolf *wo);
int					get_maze(char *name, t_wolf *wo);

/*
**	img_reader.c
*/
int					img_color(char *name, int n);
void				fill_image_buf(char *str, t_image img, char *filename);
t_image				create_image(int *mlx, char *filename);
t_image				create_xpm(int *mlx, char *filename);
void				get_images(t_wolf *wo);

/*
**	wmg_reader.c
*/
int					*new_arr(int size);
int					*fill_wimage_buf2(char *str, t_wimage wimg,
					char *name, int done);
t_wimage			new_wimage(char *name, int done);
void				get_arrays2(t_wolf *wo);
void				get_arrays(t_wolf *wo);

/*
**	ray.c
*/
void				fix_ray(t_wolf *wo, t_ray *ray, double alpha);
void				choose_a_or_b(int a, int b, double alpha, t_wolf *wo);
void				doors_and_enemies(int c, double alpha, t_wolf *wo,
				t_ray *ray);
void				rays(t_wolf *wo, int c, double alpha, int obj);
void				raycast(t_wolf *wo, t_ray *ray);

/*
**	ray2.c
*/
void				meazure_a_step(int x, int y, double alpha, t_ray *ray);
void				meazure_b_step(int x, int y, double alpha, t_ray *ray);
void				enemy_check(int x, int y, double alpha, t_wolf *wo);
int					ray_a(int y, double alpha, t_wolf *wo, int obj);
int					ray_b(int x, double alpha, t_wolf *wo, int obj);

/*
**	wall.c
*/
void				draw_greenwalls(int c, t_ray *ray, t_wolf *wo);
void				draw_quattro(int c, t_wolf *wo, t_ray *ray);
void				draw_wimage(int c, int wallnr, t_wimage wimg, t_wolf *wo);
void				draw_xmp(int c, int wallnr, t_image xpm, t_wolf *wo);
void				draw_a_wall(int c, int wallnr, t_wolf *wolf, t_ray *ray);

/*
**	wall2.c
*/
void				draw_enemy(int i, double yy, double xjump, t_wolf *wo);
void				enemy(t_wolf *wo, t_ray *ray);
int					choose_wall(t_ray *ray);
t_wimage			choose_door(t_wolf *wo);
t_wimage			choose_wimage(int wallnr, t_wolf *wo, t_ray *ray);

/*
**	shader.c
*/
int					get_r(int n);
int					get_g(int n);
int					get_b(int n);
int					shade(int n, double i);
void				paint_floor(int col, int i, int c, t_wolf *wo);

/*
**	key.c
*/
void				game_over(t_wolf *wo);
void				enemy_speaks(t_wolf *wo);
void				act(int key, t_wolf *wo);
int					deal_key(int key, t_wolf *wo);

/*
**	actions.c
*/
void				stay_round(t_wolf *wo);
int					energy(t_wolf *wo);
void				look(int key, t_wolf *wo);
void				shrink(int key, t_wolf *wo);

/*
**	shoot.c
*/
void				lazer(int a, int col, t_wolf *wo);
int					sized_a(int tiny);
int					destroy_wall(int i, t_wolf *wo);
int					build_wall(int key, t_wolf *wo);
void				shoot(int key, t_wolf *wo);

/*
**	move.c
*/
void				move_dude(t_wolf *wo, int n);
void				turn_left(t_wolf *wo);
void				turn_right(t_wolf *wo);
void				walk(t_wolf *wo);
void				walk_back(t_wolf *wo);

/*
**move2.c
*/
void				go(int movex, int movey, t_wolf *wo);
void				bounce_wall(t_wolf *wo);
int					not_corner(int try_x, int try_y, t_wolf *wo);
void				corner(int c, int wallnr, t_wolf *wo);
void				fix_corner(int obj, int wallnr, int c, t_wolf *wo);

/*
**	color.c
*/
int					col(int c);
int					energy_color(int n);
int					green3(int row);
int					green2(int row);
int					greenwalls(int row);

#endif
