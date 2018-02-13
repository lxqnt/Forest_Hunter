/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquint <aquint@42.us.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 17:41:17 by aquint            #+#    #+#             */
/*   Updated: 2018/01/19 16:10:07 by aquint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	dda_towall(t_player *plyr, t_win *wolf)
{
	plyr->wall = 0;
	while (plyr->wall == 0)
	{
		if (plyr->dist_nextx < plyr->dist_nexty)
		{
			plyr->dist_nextx += plyr->delta_x;
			plyr->map_x += plyr->stepx;
			plyr->w_side = 0;
		}
		else
		{
			plyr->dist_nexty += plyr->delta_y;
			plyr->map_y += plyr->stepy;
			plyr->w_side = 1;
		}
		if (wolf->map[plyr->map_x][plyr->map_y] > 0)
			plyr->wall = 1;
	}
}

void	vert_line_set(t_player *plyr, t_win *wolf)
{
	int vert_height;

	if (plyr->w_side == 0)
		plyr->w_dst = (plyr->map_x - plyr->x + (1 - plyr->stepx) / 2) /
	plyr->ray_dir_x;
	else
		plyr->w_dst = (plyr->map_y - plyr->y + (1 - plyr->stepy) / 2) /
	plyr->ray_dir_y;
	vert_height = (int)(wolf->sz_y / plyr->w_dst);
	plyr->draw_start = -vert_height / 2 + wolf->sz_y / 2;
	if (plyr->draw_start < 0)
		plyr->draw_start = 0;
	plyr->draw_end = vert_height / 2 + wolf->sz_y / 2;
	if (plyr->draw_end >= wolf->sz_y)
		plyr->draw_end = wolf->sz_y - 1;
	plyr->vert_height = vert_height;
}

void	f_direction(t_player *plyr)
{
	if (plyr->ray_dir_x < 0)
	{
		plyr->stepx = -1;
		plyr->dist_nextx = (plyr->x - plyr->map_x) * plyr->delta_x;
	}
	else
	{
		plyr->stepx = 1;
		plyr->dist_nextx = (1 + plyr->map_x - plyr->x) * plyr->delta_x;
	}
	if (plyr->ray_dir_y < 0)
	{
		plyr->stepy = -1;
		plyr->dist_nexty = (plyr->y - plyr->map_y) * plyr->delta_y;
	}
	else
	{
		plyr->stepy = 1;
		plyr->dist_nexty = (1 + plyr->map_y - plyr->y) * plyr->delta_y;
	}
}

void	run_screen(t_win *wolf)
{
	t_player	*plyr;
	int			x;

	mlx_clear_window(wolf->mlx, wolf->win);
	plyr = wolf->plyr;
	img_set(wolf, &wolf->frame, wolf->sz_x, wolf->sz_y);
	background_color(wolf);
	x = -1;
	while (++x < wolf->sz_x)
	{
		plyr->cam_x = 2 * x / (double)wolf->sz_x - 1;
		plyr->ray_dir_x = plyr->dir_x + plyr->pl_cam_x * plyr->cam_x;
		plyr->ray_dir_y = plyr->dir_y + plyr->pl_cam_y * plyr->cam_x;
		plyr->map_x = (int)plyr->x;
		plyr->map_y = (int)plyr->y;
		plyr->delta_x = fabs(1 / plyr->ray_dir_x);
		plyr->delta_y = fabs(1 / plyr->ray_dir_y);
		f_direction(plyr);
		dda_towall(plyr, wolf);
		vert_line_set(plyr, wolf);
		texture_set(plyr, wolf, x);
	}
	mlx_put_image_to_window(wolf->mlx, wolf->win, wolf->frame.img, 0, 0);
	get_time(wolf->plyr);
	mlx_destroy_image(wolf->mlx, wolf->frame.img);
}
