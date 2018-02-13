/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquint <aquint@42.us.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 11:15:17 by aquint            #+#    #+#             */
/*   Updated: 2018/02/13 00:34:28 by aquint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		main(int argc, char **argv)
{
	t_win	*wolf;
	int		i;

	if (argc > 1 && argc < 5)
	{
		i = 0;
		wolf = (t_win*)ft_memalloc(sizeof(t_win));
		wolf->plyr = (t_player*)ft_memalloc(sizeof(t_player));
		wolf->level = (char**)ft_memalloc(sizeof(char*) * argc);
		while (++i < argc)
			wolf->level[i - 1] = ft_strdup(argv[i]);
		set_window(wolf, 640, 480);
		homescreen(wolf, argc);
		mlx_hook(wolf->win, 2, 3, x_win, wolf);
		mlx_hook(wolf->win, 17, 0, ex_win, wolf);
		mlx_loop(wolf->mlx);
	}
	else
		run_error(1, NULL);
	return (0);
}
