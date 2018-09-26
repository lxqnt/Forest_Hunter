/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquint <aquint@42.us.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 22:13:55 by aquint            #+#    #+#             */
/*   Updated: 2018/01/19 16:04:29 by aquint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		del_textures(t_win *wolf)
{
	t_img	*tmp;

	while (wolf->tx)
	{
		tmp = wolf->tx->next;
		mlx_destroy_image(wolf->mlx, wolf->tx->img);
		wolf->tx->img_loc = NULL;
		free(wolf->tx);
		wolf->tx = tmp;
	}
}

static int		check_perimeter(t_win *wolf)
{
	int y;
	int x;

	y = 0;
	x = 0;
	if (wolf->mx <= 2 || wolf->my <= 2)
		return (-1);
	while (x < wolf->mx)
	{
		if (wolf->map[0][x] < 1 || wolf->map[wolf->my - 1][x] < 1)
			return (-1);
		x++;
	}
	while (y < wolf->my)
	{
		if (wolf->map[y][0] < 1 || wolf->map[y][wolf->mx - 1] < 1)
			return (-1);
		y++;
	}
	return (0);
}

int				run_error(int err, t_win *wolf)
{
	int		i;

	i = 0;
	if (err == 1)
	{
		ft_putstr("usage: ./foresthunter [level map file . .][...][...]\n");
		ft_putstr("error: only 1 - 3 level maps accepted\n");
		return (0);
	}
	if (err == -1)
		ft_putstr("error: level map file / format\n");
	if (wolf->level)
		ft_freearray((void**)wolf->level);
	if (wolf->tx)
		del_textures(wolf);
	if (wolf->map)
		ft_freearray((void**)wolf->map);
	free(wolf->plyr);
	mlx_destroy_window(wolf->mlx, wolf->win);
	free(wolf);
	system("Killall afplay");
	exit(0);
}

int				copy_map(t_win *wolf, char *buf, int ix)
{
	int		len;
	int		i;
	char	num;

	len = ft_strlen(buf);
	if (wolf->my > 0)
	{
		if (len != wolf->mx)
			return (-1);
	}
	i = 0;
	if (!(wolf->map[ix] = (int*)malloc(sizeof(int) * len)))
		return (-1);
	while (buf[i] != '\0')
	{
		num = buf[i];
		if (num < 48 || num > 57)
			return (-1);
		wolf->map[ix][i] = ft_atoi(&num);
		i++;
	}
	wolf->mx = len;
	return (0);
}

int				read_map(t_win *wolf, char *str)
{
	int		fd;
	int		ret;
	char	*buf;

	wolf->my = 0;
	if (!(wolf->map = (int**)ft_memalloc(sizeof(wolf->map) * 65)))
		return (-1);
	if ((fd = open(str, O_RDONLY)) > 0)
	{
		while ((ret = get_next_line(fd, &buf)) == 1)
		{
			if (wolf->my == 64)
				return (-1);
			if (copy_map(wolf, buf, wolf->my) == -1)
				return (-1);
			wolf->my++;
			free(buf);
		}
		if (close(fd) == -1)
			return (-1);
		if (check_perimeter(wolf) == -1)
			return (-1);
		return (ret);
	}
	return (fd);
}
