/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquint <aquint@42.us.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 12:33:50 by aquint            #+#    #+#             */
/*   Updated: 2018/01/20 00:31:02 by aquint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	rotate(int keycode, t_player *plyr)
{
	double	rs;
	double	old_dir_x;
	double	old_pl_cam_x;

	old_dir_x = plyr->dir_x;
	old_pl_cam_x = plyr->pl_cam_x;
	if (keycode == 123)
	{
		rs = (plyr->frametime * 135) / 3.14159;
		plyr->dir_x = plyr->dir_x * cos(rs) - plyr->dir_y * sin(rs);
		plyr->dir_y = old_dir_x * sin(rs) + plyr->dir_y * cos(rs);
		plyr->pl_cam_x = plyr->pl_cam_x * cos(rs) - plyr->pl_cam_y * sin(rs);
		plyr->pl_cam_y = old_pl_cam_x * sin(rs) + plyr->pl_cam_y * cos(rs);
	}
	else if (keycode == 124)
	{
		rs = (plyr->frametime * 135) / 3.14159;
		plyr->dir_x = plyr->dir_x * cos(-rs) - plyr->dir_y * sin(-rs);
		plyr->dir_y = old_dir_x * sin(-rs) + plyr->dir_y * cos(-rs);
		plyr->pl_cam_x = plyr->pl_cam_x * cos(-rs) - plyr->pl_cam_y * sin(-rs);
		plyr->pl_cam_y = old_pl_cam_x * sin(-rs) + plyr->pl_cam_y * cos(-rs);
	}
	else
		return (0);
	return (1);
}

static int	move(int keycode, t_win *wolf, t_player *plyr)
{
	double	mvs;

	mvs = plyr->frametime * 80.00;
	if (keycode == 126)
	{
		if (wolf->map[(int)(plyr->x + plyr->dir_x * mvs)][(int)plyr->y] == 0)
			plyr->x += plyr->dir_x * mvs;
		if (wolf->map[(int)plyr->x][(int)(plyr->y + plyr->dir_y * mvs)] == 0)
			plyr->y += plyr->dir_y * mvs;
	}
	else if (keycode == 125)
	{
		if (wolf->map[(int)(plyr->x - plyr->dir_x * mvs)][(int)plyr->y] == 0)
			plyr->x -= plyr->dir_x * mvs;
		if (wolf->map[(int)plyr->x][(int)(plyr->y - plyr->dir_y * mvs)] == 0)
			plyr->y -= plyr->dir_y * mvs;
	}
	else
		return (0);
	return (1);
}

static int	level(int keycode, t_win *wolf)
{
	int error;

	if (keycode >= 18 && keycode <= 20 && wolf->lvl_select != -1)
	{
		if (keycode - 17 <= wolf->lvl)
		{
			wolf->lvl = keycode - 17;
			wolf->lvl_select = 1;
			error = read_map(wolf, wolf->level[wolf->lvl - 1]);
			mlx_clear_window(wolf->mlx, wolf->win);
			if (error != -1)
			{
				load_textures(wolf);
				set_start(wolf->plyr, wolf);
				return (1);
			}
			else
				run_error(error, wolf);
		}
	}
	return (0);
}

int			x_win(int keycode, t_win *wolf)
{
	int	reset;
	int x;
	int y;

	x = (int)(wolf->plyr->x + wolf->plyr->dir_x);
	y = (int)(wolf->plyr->y + wolf->plyr->dir_y);
	reset = 0;
	if (wolf->lvl_select <= 0)
		reset += level(keycode, wolf);
	else
	{
		if (wolf->map[x][y] == 1)
			return (finish(wolf));
		reset += move(keycode, wolf, wolf->plyr);
		reset += rotate(keycode, wolf->plyr);
		if (keycode == 46)
			map_location(wolf);
	}
	if (keycode == 53 || keycode == 12)
		run_error(0, wolf);
	if (reset >= 1)
		run_screen(wolf);
	return (0);
}

int			ex_win(t_win *wolf)
{
	run_error(0, wolf);
	return (0);
}
