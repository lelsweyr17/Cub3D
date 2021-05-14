/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 18:04:13 by lelsweyr          #+#    #+#             */
/*   Updated: 2021/02/08 13:01:55 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcer.h"

void		sprites_2(t_elems *elem, int i)
{
	elem->spr[i].ray = sqrt(pow(elem->spr[i].x - elem->plr_x, 2) +
	pow(elem->spr[i].y - elem->plr_y, 2));
	elem->spr[i].alfa = acos(fabs(elem->spr[i].x - elem->plr_x) /
	elem->spr[i].ray);
	if (elem->spr[i].x < elem->plr_x && elem->spr[i].y < elem->plr_y)
		elem->spr[i].alfa += M_PI;
	if (elem->spr[i].x >= elem->plr_x && elem->spr[i].y < elem->plr_y)
		elem->spr[i].alfa = 2 * M_PI - elem->spr[i].alfa;
	else if (elem->spr[i].x < elem->plr_x && elem->spr[i].y >= elem->plr_y)
		elem->spr[i].alfa = M_PI - elem->spr[i].alfa;
}

void		sprites(t_elems *elem, int i)
{
	float	delta;

	sprites_2(elem, i);
	if (fabs(elem->spr[i].alfa - elem->plr_a) > 3 * M_PI / 2)
	{
		if (elem->spr[i].alfa > 3 * M_PI / 2)
			elem->spr[i].alfa -= 2 * M_PI;
		else
			elem->spr[i].alfa += 2 * M_PI;
	}
	if ((delta = fabs(elem->spr[i].alfa - elem->plr_a)) > M_PI / 6 + 0.1)
		delta = M_PI / 6 + 0.1;
	elem->spr[i].wall_dist = elem->spr[i].ray * cos(delta);
	elem->spr[i].wall_height = (int)(elem->map_x /
		fabs(elem->spr[i].wall_dist));
	elem->spr[i].left = elem->spr[i].alfa - elem->spr[i].wall_height / 2 *
	M_PI / 3 / elem->map_x;
	elem->spr[i].right = elem->spr[i].alfa + elem->spr[i].wall_height / 2 *
	M_PI / 3 / elem->map_x;
}

void		draw_init_2(t_elems *elem, int i, int start, int end)
{
	if (elem->spr[i].wall_height >= elem->map_x)
	{
		if (start == 0 && end > elem->map_x - 1)
		{
			elem->spr->pxl_start = (elem->spr[i].wall_height - end) *
			elem->spr->pxl_step;
			elem->spr->pxl_end = 64 - (elem->spr[i].wall_height - end) *
			elem->spr->pxl_step;
		}
		else if (start == 0 && end <= elem->map_x - 1)
			elem->spr->pxl_start = (elem->spr[i].wall_height - end) *
			elem->spr->pxl_step;
		else if (end == elem->map_x - 1 && start > 0)
			elem->spr->pxl_end = 64 - (elem->spr[i].wall_height -
			(end - start)) * elem->spr->pxl_step;
	}
	if (end >= elem->map_x)
		end = elem->map_x - 1;
}

void		draw_init(t_elems *elem, int start, int end, int i)
{
	elem->spr->pxl_start = 0;
	elem->spr->pxl_end = 64;
	elem->spr->pxl_up = 0;
	elem->spr->pxl_down = 64;
	elem->spr->pxl_step = (float)64 / elem->spr[i].wall_height;
	if (start == 0 && elem->spr[i].wall_height < elem->map_x)
		elem->spr->pxl_start = (elem->spr[i].wall_height - end) *
		elem->spr->pxl_step;
	if (end == (elem->map_x - 1) && elem->spr[i].wall_height < elem->map_x)
		elem->spr->pxl_end = (end - start) * elem->spr->pxl_step;
	draw_init_2(elem, i, start, end);
	if (elem->spr[i].wall_height > elem->map_y)
	{
		elem->spr->pxl_up = (elem->spr[i].wall_height / 2 - elem->map_y / 2) *
		elem->spr->pxl_step;
		elem->spr->pxl_down = 64 - ((elem->spr[i].wall_height / 2 -
		elem->map_y / 2) * elem->spr->pxl_step);
	}
}

void		draw_spr(int start, int end, t_elems *elem, int i)
{
	draw_init(elem, start, end, i);
	draw_sprite(elem, i, start, end);
	if (end > elem->map_x - 1)
		end = elem->map_x - 1;
	while (start <= end)
	{
		if ((elem->up = elem->map_y / 2 - elem->spr[i].wall_height / 2) < 0)
			elem->up = 0;
		elem->spr->pxl_up = (elem->spr[i].wall_height / 2 - elem->map_y / 2) *
		elem->spr->pxl_step;
		if (elem->spr[i].wall_height < elem->map_y)
			elem->spr->pxl_up = 0;
		if (elem->pxl_spr[start] == 2)
			while (elem->spr->pxl_up < 64)
			{
				if (tex_color(&elem->texts[0], elem->spr->pxl_start,
					elem->spr->pxl_up) != 0)
					my_mlx_pp(elem, start, elem->up, tex_color(&elem->texts[0],
					elem->spr->pxl_start, elem->spr->pxl_up));
				elem->up += 1;
				elem->spr->pxl_up += elem->spr->pxl_step;
			}
		elem->spr->pxl_start += elem->spr->pxl_step;
		start += 1;
	}
}
