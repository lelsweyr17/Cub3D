/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 18:03:18 by lelsweyr          #+#    #+#             */
/*   Updated: 2021/02/07 20:52:12 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcer.h"

void		euclidean(t_elems *elem, int i)
{
	float	x;
	float	y;
	float	c;

	c = 0;
	elem->param.cos = 0;
	while (!elem->param.cos)
	{
		x = elem->plr_x + c * cos(elem->walls.dir);
		y = elem->plr_y + c * sin(elem->walls.dir);
		if (elem->map[(int)y][(int)x] == '1')
		{
			if (elem->map[(int)(y - 0.005 * sin(elem->walls.dir))]
				[(int)x] == '1')
				elem->param.cos = 1;
			elem->wall[i] = c;
			elem->tex_p.x = x;
			elem->tex_p.y = y;
			break ;
		}
		c += 0.004;
	}
}

void		wall_height(t_elems *elem, int i)
{
	elem->walls.ray_dir = 1 / cos(elem->walls.dir - elem->plr_a);
	elem->walls.wall_dist = (elem->wall[i] / fabs(elem->walls.ray_dir));
	elem->walls.line_heignt = (int)(elem->map_x / elem->walls.wall_dist);
	elem->walls.draw_start = -elem->walls.line_heignt / 2 + elem->map_y / 2;
	if (elem->walls.draw_start < 0)
		elem->walls.draw_start = 0;
	elem->walls.draw_end = elem->walls.line_heignt / 2 + elem->map_y / 2;
	if (elem->walls.draw_end >= elem->map_y)
		elem->walls.draw_end = elem->map_y - 1;
}

void		init(t_elems *elem)
{
	elem->param.n_side = 0;
	elem->param.e_side = 0;
	elem->param.s_side = 0;
	elem->param.w_side = 0;
	if (elem->plr_a < 0)
		elem->plr_a += 2 * M_PI;
	if (elem->plr_a >= 2 * M_PI)
		elem->plr_a -= 2 * M_PI;
	if (elem->walls.dir < 0)
		elem->walls.dir += 2 * M_PI;
	if (elem->walls.dir >= 2 * M_PI)
		elem->walls.dir -= 2 * M_PI;
}

void		side(t_elems *elem)
{
	init(elem);
	if (elem->walls.dir >= 0 && elem->walls.dir <= (M_PI / 2))
	{
		elem->param.e_side = (elem->param.cos == 1 ? 1 : 0);
		elem->param.s_side = (elem->param.cos == 1 ? 0 : 1);
	}
	else if (elem->walls.dir > M_PI / 2 && elem->walls.dir <= M_PI)
	{
		elem->param.w_side = (elem->param.cos == 1 ? 1 : 0);
		elem->param.s_side = (elem->param.cos == 1 ? 0 : 1);
	}
	else if (elem->walls.dir > M_PI && elem->walls.dir <= (3 * M_PI / 2))
	{
		elem->param.w_side = (elem->param.cos == 1 ? 1 : 0);
		elem->param.n_side = (elem->param.cos == 1 ? 0 : 1);
	}
	else if (elem->walls.dir > (3 * M_PI / 2) && elem->walls.dir < (2 * M_PI))
	{
		elem->param.e_side = (elem->param.cos == 1 ? 1 : 0);
		elem->param.n_side = (elem->param.cos == 1 ? 0 : 1);
	}
}

void		map_3d(t_elems *elem)
{
	int		i;

	i = -1;
	init(elem);
	elem->walls.dir = elem->plr_a - M_PI / 6;
	while (++i < elem->map_x)
	{
		side(elem);
		euclidean(elem, i);
		wall_height(elem, i);
		draw_tex(elem, i);
		draw_3d(elem, i);
		elem->walls.dir += 60 / ((float)elem->map_x * 180 / M_PI);
	}
	i = -1;
	sort_sprites(elem);
	while (++i < elem->count)
	{
		sprites(elem, elem->sprites[i]);
		part_spr(elem, elem->sprites[i]);
	}
}
