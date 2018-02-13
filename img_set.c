/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquint <aquint@42.us.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 12:33:50 by aquint            #+#    #+#             */
/*   Updated: 2018/02/13 00:34:49 by aquint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			homescreen(t_win *wolf, int argc)
{
	int x;
	int y;

	x = wolf->sz_x;
	y = wolf->sz_y;
	wolf->homescreen.x = wolf->sz_x;
	wolf->homescreen.y = wolf->sz_y;
	wolf->lvl = argc - 1;
	wolf->lvl_select = 0;
	wolf->homescreen.img = mlx_xpm_file_to_image(wolf->mlx,
		"textures/forest.xpm", &x, &y);
	mlx_put_image_to_window(wolf->mlx, wolf->win, wolf->homescreen.img, 0, 0);
	if (wolf->lvl >= 1)
		mlx_string_put(wolf->mlx, wolf->win, 220, 350, 0xFFFFFF,
			"Press 1 for Level 1 ");
	if (wolf->lvl >= 2)
		mlx_string_put(wolf->mlx, wolf->win, 220, 375, 0xFFFFFF,
			"Press 2 for Level 2");
	if (wolf->lvl >= 3)
		mlx_string_put(wolf->mlx, wolf->win, 220, 400, 0xFFFFFF,
			"Press 3 for Level 3");
	mlx_destroy_image(wolf->mlx, wolf->homescreen.img);
	system("afplay textures/stickerbrush.mp3 &");
}

int				finish(t_win *wolf)
{
	int	x;
	int	y;
	int i;

	i = 0;
	x = wolf->sz_x;
	y = wolf->sz_y;
	mlx_clear_window(wolf->mlx, wolf->win);
	wolf->homescreen.img = mlx_xpm_file_to_image(wolf->mlx,
		"textures/finish.xpm", &x, &y);
	mlx_put_image_to_window(wolf->mlx, wolf->win, wolf->homescreen.img, 0, 0);
	mlx_destroy_image(wolf->mlx, wolf->homescreen.img);
	mlx_string_put(wolf->mlx, wolf->win, 180, 40, 0xFFFFFF,
		"YOU FOUND THE ANCIENT CITY!");
	wolf->lvl_select = -1;
	return (0);
}

void			map_location(t_win *wolf)
{
	int x;
	int y;
	int num;

	x = 0;
	y = 0;
	wolf->map[(int)wolf->plyr->x][(int)wolf->plyr->y] = 9;
	while (y < wolf->my)
	{
		x = 0;
		while (x < wolf->mx)
		{
			num = wolf->map[y][x];
			if (num == 9)
				ft_putchar('@');
			else if (num == 0)
				ft_putchar(' ');
			else
				ft_putchar('#');
			x++;
		}
		ft_putchar('\n');
		y++;
	}
	wolf->map[(int)wolf->plyr->x][(int)wolf->plyr->y] = 0;
}

unsigned int	*img_mem(void *img, int x)
{
	int				bpp;
	int				en;
	int				b;
	unsigned int	*loc;

	bpp = 0;
	en = 1;
	b = x;
	loc = (unsigned int*)mlx_get_data_addr(img, &bpp, &b, &en);
	return (loc);
}

t_img			*img_set(t_win *wolf, t_img *set, int x, int y)
{
	set->img_loc = NULL;
	set->x = x;
	set->y = y;
	set->img = mlx_new_image(wolf->mlx, set->x, set->y);
	set->img_loc = img_mem(set->img, x);
	return (set);
}
