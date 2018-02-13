/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquint <aquint@42.us.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 17:41:17 by aquint            #+#    #+#             */
/*   Updated: 2018/01/17 23:23:12 by aquint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	set_start(t_player *plyr, t_win *wolf)
{
	plyr->y = 1.5;
	plyr->x = 1.5;
	while (wolf->map[(int)plyr->x][(int)plyr->y] != 0)
	{
		plyr->x += 1.0;
		if ((int)plyr->x == wolf->my)
		{
			plyr->y += 1.0;
			plyr->x = 1.0;
		}
		if ((int)plyr->y == wolf->mx)
		{
			wolf->map[1][1] = 0;
			plyr->y = 1.5;
			plyr->x = 1.5;
		}
	}
	plyr->dir_x = -1;
	plyr->dir_y = 0;
	plyr->pl_cam_x = 0;
	plyr->pl_cam_y = 0.66;
	plyr->t_old = 0;
	plyr->t_new = clock();
}

int		set_window(t_win *wolf, int x, int y)
{
	wolf->sz_x = x;
	wolf->sz_y = y;
	if (!(wolf->mlx = mlx_init()))
		return (-1);
	if (!(wolf->win = mlx_new_window(wolf->mlx, x, y, "Wolf")))
		return (-1);
	return (0);
}

void	get_time(t_player *plyr)
{
	plyr->t_old = plyr->t_new;
	plyr->t_new = clock();
	plyr->frametime = (double)(plyr->t_new - plyr->t_old) / CLOCKS_PER_SEC;
	if (plyr->frametime > 1)
		plyr->frametime = 1;
	if (plyr->frametime == 0)
		plyr->frametime += 0.01;
}
