/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 18:04:19 by lelsweyr          #+#    #+#             */
/*   Updated: 2021/02/08 15:12:52 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcer.h"

void			my_mlx_pp(t_elems *elem, int x, int y, int color)
{
	char		*dst;

	dst = elem->data.addr + (y * elem->data.line_length +
	x * (elem->data.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int				map_mlx(t_elems *elem)
{
	int			i;
	int			j;

	i = -1;
	j = 0;
	elem->x = 0;
	elem->y = 0;
	map_3d(elem);
	if (elem->save)
	{
		bmp_scr(elem, "screenshot.bmp");
		exit(0);
	}
	if (elem->move.save && elem->move.back)
		bmp_scr(elem, "screenshot_game.bmp");
	mlx_put_image_to_window(elem->mlx, elem->win, elem->img, 0, 0);
	mlx_destroy_image(elem->mlx, elem->img);
	elem->img = mlx_new_image(elem->mlx, elem->map_x, elem->map_y);
	key_hook(elem);
	return (0);
}

void			map_2d(t_elems *elem)
{
	ft_plr(elem);
	elem->plr_x += 0.5;
	elem->plr_y += 0.5;
	elem->mlx = mlx_init();
	elem->win = mlx_new_window(elem->mlx, elem->map_x, elem->map_y, "Cub3D");
	elem->img = mlx_new_image(elem->mlx, elem->map_x, elem->map_y);
	elem->data.addr = mlx_get_data_addr(elem->img, &elem->data.bits_per_pixel,
			&elem->data.line_length, &elem->data.endian);
	textures(elem);
	count_sprite(elem);
	elem->sprites = (int *)ft_calloc(elem->count, sizeof(int));
	elem->wall = (float *)ft_calloc(elem->map_x, sizeof(float));
	elem->pxl_spr = (int *)ft_calloc(elem->map_x, sizeof(int));
	mlx_hook(elem->win, 2, 0, key_press, elem);
	mlx_hook(elem->win, 3, 1, key_release, elem);
	mlx_hook(elem->win, 17, 0, exit_cube, elem);
	mlx_loop_hook(elem->mlx, map_mlx, elem);
	mlx_loop(elem->mlx);
}

void			check_save(t_elems *elem, char *argv)
{
	if (ft_strlen(argv) == 6)
		if (ft_strncmp(argv, "--save", 6) == 0)
			elem->save = 1;
		else
			errors(12);
	else
		errors(12);
}

int				main(int argc, char **argv)
{
	t_list		*st;
	t_elems		*elem;

	st = (t_list *)ft_calloc(1, sizeof(t_list));
	elem = (t_elems *)ft_calloc(1, sizeof(t_elems));
	if (argc == 1)
		errors(10);
	if (argc == 3)
		check_save(elem, argv[2]);
	ft_gnl(argv[1], st, elem);
	map_2d(elem);
	return (0);
}
