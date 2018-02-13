/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquint <aquint@42.us.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 10:25:34 by aquint            #+#    #+#             */
/*   Updated: 2018/01/20 00:32:47 by aquint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "./libft/libft.h"
# include "./minilibx/mlx.h"
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <time.h>

typedef struct	s_player
{
	double			x;
	double			y;
	double			dir_x;
	double			dir_y;
	double			pl_cam_x;
	double			pl_cam_y;
	clock_t			t_old;
	clock_t			t_new;
	double			frametime;
	double			cam_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			dist_nextx;
	double			dist_nexty;
	double			delta_x;
	double			delta_y;
	double			w_dst;
	int				stepx;
	int				stepy;
	int				wall;
	int				w_side;
	int				vert_height;
	int				draw_start;
	int				draw_end;

}				t_player;

typedef struct	s_img
{
	void			*img;
	int				x;
	int				y;
	int				i;
	int				pxl;
	unsigned int	*img_loc;
	struct s_img	*next;
}				t_img;

typedef	struct	s_win
{
	t_player		*plyr;
	int				**map;
	char			**level;
	void			*mlx;
	void			*win;
	int				mx;
	int				my;
	int				sz_x;
	int				sz_y;
	int				lvl;
	int				lvl_select;
	t_img			homescreen;
	t_img			frame;
	t_img			*tx;
}				t_win;

/*
** raycasting d
*/

void			get_time(t_player *plyr);
void			f_direction(t_player *plyr);
void			vert_line_set(t_player *plyr, t_win *wolf);
void			dda_towall(t_player *plyr, t_win *wolf);
void			get_time(t_player *plyr);
void			f_direction(t_player *plyr);

/*
** setup
*/

int				set_window(t_win *wolf, int x, int y);
void			set_start(t_player *plyr, t_win *wolf);
void			run_screen(t_win *wolf);

/*
** textures and imgs
*/

void			background_color(t_win *wolf);
void			load_textures(t_win *wolf);
t_img			*texture_img(t_win *wolf, char *str);
void			texture_set(t_player *plyr, t_win *wolf, int x);
void			place_texture(t_img *tx, t_win *wolf, int tex_x, int x);
void			homescreen(t_win *wolf, int argc);
void			map_location(t_win *wolf);
unsigned int	*img_mem(void *img, int x);
t_img			*img_set(t_win *wolf, t_img *set, int x, int y);
int				finish(t_win *wolf);

/*
** map read and error
*/

int				run_error(int err, t_win *wolf);
int				copy_map(t_win *wolf, char *buf, int ix);
int				read_map(t_win *wolf, char *str);

/*
** key_hooks.c && mouse_hooks.c
*/

int				x_win(int keycode, t_win *wolf);
int				ex_win(t_win *wolf);

#endif
