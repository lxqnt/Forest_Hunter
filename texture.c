/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquint <aquint@42.us.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 17:41:17 by aquint            #+#    #+#             */
/*   Updated: 2018/01/19 22:19:19 by aquint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	load_textures(t_win *wolf)
{
	if (wolf->lvl % 2 == 1)
	{
		wolf->tx = texture_img(wolf, "textures/finish.xpm");
		wolf->tx = texture_img(wolf, "textures/forest1.xpm");
		wolf->tx = texture_img(wolf, "textures/leaves.xpm");
		wolf->tx = texture_img(wolf, "textures/rock_1.xpm");
		wolf->tx = texture_img(wolf, "textures/wood.xpm");
	}
	if (wolf->lvl % 2 == 0)
	{
		wolf->tx = texture_img(wolf, "textures/finish.xpm");
		wolf->tx = texture_img(wolf, "textures/darkforest.xpm");
		wolf->tx = texture_img(wolf, "textures/bamboo2.xpm");
		wolf->tx = texture_img(wolf, "textures/rock_1.xpm");
		wolf->tx = texture_img(wolf, "textures/leaves.xpm");
	}
}

t_img	*texture_img(t_win *wolf, char *str)
{
	t_img	*tmp;
	t_img	*new;

	new = (t_img*)ft_memalloc(sizeof(t_img));
	new->i = -1;
	new->img = mlx_xpm_file_to_image(wolf->mlx, str, &new->x, &new->y);
	new->img_loc = img_mem(new->img, 64);
	new->next = NULL;
	if (!(wolf->tx))
		wolf->tx = new;
	tmp = wolf->tx;
	while (tmp->next != NULL)
		tmp = tmp->next;
	new->i = tmp->i + 1;
	if (new != wolf->tx)
		tmp->next = new;
	return (wolf->tx);
}

void	texture_set(t_player *plyr, t_win *wolf, int x)
{
	int		texnum;
	double	wallx;
	int		tex_x;
	t_img	*tmp;

	tmp = wolf->tx;
	texnum = wolf->map[plyr->map_x][plyr->map_y] - 1;
	while (tmp->next != NULL && tmp->i != texnum)
		tmp = tmp->next;
	if (plyr->w_side == 0)
		wallx = plyr->y + plyr->w_dst * plyr->ray_dir_y;
	else
		wallx = plyr->x + plyr->w_dst * plyr->ray_dir_x;
	wallx -= floor(wallx);
	tex_x = (int)(wallx * (double)(tmp->x));
	if (plyr->w_side == 0 && plyr->ray_dir_x > 0)
		tex_x = tmp->x - tex_x - 1;
	if (plyr->w_side == 1 && plyr->ray_dir_y < 0)
		tex_x = tmp->x - tex_x - 1;
	place_texture(tmp, wolf, tex_x, x);
}

void	place_texture(t_img *tx, t_win *wolf, int tex_x, int x)
{
	int pxl;
	int endpxl;
	int y;
	int d;
	int tex_y;

	pxl = x + (wolf->plyr->draw_start * wolf->sz_x);
	endpxl = x + (wolf->plyr->draw_end * wolf->sz_x);
	y = wolf->plyr->draw_start;
	tx->pxl = tex_x;
	while (pxl < endpxl)
	{
		d = y * 256 - wolf->sz_y * 128 + wolf->plyr->vert_height * 128;
		tex_y = ((d * tx->x) / wolf->plyr->vert_height) / 256;
		tx->pxl = (tx->y * tex_y + tex_x);
		wolf->frame.img_loc[pxl] = tx->img_loc[tx->pxl];
		tx->pxl = (tx->y * tex_y + tex_x);
		pxl += wolf->sz_x;
		y++;
	}
}

void	background_color(t_win *wolf)
{
	int				endpxl;
	int				i;
	unsigned int	clr;
	unsigned int	clr1;

	i = 1;
	endpxl = wolf->sz_x * wolf->sz_y;
	if (wolf->lvl % 2 == 1)
	{
		clr1 = mlx_get_color_value(wolf->mlx, 0x0B5345);
		clr = mlx_get_color_value(wolf->mlx, 0x85C1E9);
	}
	if (wolf->lvl % 2 == 0)
	{
		clr = mlx_get_color_value(wolf->mlx, 0x2E4053);
		clr1 = mlx_get_color_value(wolf->mlx, 0x49311c);
	}
	while (i < (endpxl / 2))
	{
		wolf->frame.img_loc[i++] = clr;
	}
	while (i < endpxl)
		wolf->frame.img_loc[i++] = clr1;
}
