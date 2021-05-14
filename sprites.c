/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 18:04:10 by lelsweyr          #+#    #+#             */
/*   Updated: 2021/02/07 22:14:07 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcer.h"

void		sprite_cases(t_elems *elem, int pxl1, int pxl2, int i)
{
	elem->delta = (float)1 / (pxl2 - pxl1);
	if (pxl1 >= 0 && pxl2 < elem->map_x)
		draw_spr(pxl1, pxl2, elem, i);
	else if (pxl1 < 0 && pxl2 >= 0 && pxl2 < elem->map_x)
	{
		pxl1 = 0;
		draw_spr(pxl1, pxl2, elem, i);
	}
	else if (pxl1 < 0 && pxl2 >= elem->map_x)
	{
		pxl1 = 0;
		draw_spr(pxl1, pxl2, elem, i);
	}
	else if (pxl1 >= 0 && pxl1 < elem->map_x && pxl2 >= elem->map_x)
	{
		pxl2 = elem->map_x - 1;
		draw_spr(pxl1, pxl2, elem, i);
	}
}

void		draw_sprite(t_elems *elem, int i, int pxl1, int pxl2)
{
	float	ray;
	float	dx;
	float	deg;

	deg = elem->spr[i].left;
	dx = abs(pxl1 - elem->map_x / 2) * elem->delta;
	while (pxl1 <= pxl2)
	{
		elem->pxl_spr[pxl1] = 0;
		ray = sqrt(pow(dx, 2) + pow(elem->spr[i].wall_dist, 2));
		if (ray <= (elem->wall[pxl1] + 0.2))
			elem->pxl_spr[pxl1] = 2;
		deg += M_PI / 3 / elem->map_x;
		pxl1++;
		dx += elem->delta;
	}
}

void		part_spr(t_elems *elem, int i)
{
	int		pxl1;
	int		pxl2;
	float	deg;

	deg = elem->plr_a - M_PI / 6;
	pxl1 = (elem->spr[i].left - deg) / (M_PI / 3 / elem->map_x);
	pxl2 = pxl1 + elem->spr[i].wall_height;
	sprite_cases(elem, pxl1, pxl2, i);
}

void		sprite_rays(t_elems *elem, float *str)
{
	int		i;
	int		k;
	float	tmpf;
	int		tmp;

	i = -1;
	while (++i < elem->count)
	{
		k = i + 1;
		while (--k > 0 && str[k - 1] < str[k])
		{
			tmpf = str[k - 1];
			str[k - 1] = str[k];
			str[k] = tmpf;
			tmp = elem->sprites[k - 1];
			elem->sprites[k - 1] = elem->sprites[k];
			elem->sprites[k] = tmp;
		}
	}
}

void		sort_sprites(t_elems *elem)
{
	int		i;
	int		k;
	float	str[elem->count];

	i = -1;
	k = 0;
	while (++i < elem->count)
	{
		elem->spr[i].ray = sqrt(pow(elem->spr[i].x - elem->plr_x, 2) +
		pow(elem->spr[i].y - elem->plr_y, 2));
		str[i] = elem->spr[i].ray;
		elem->sprites[k++] = i;
	}
	sprite_rays(elem, str);
}
