/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 18:46:25 by lelsweyr          #+#    #+#             */
/*   Updated: 2021/02/08 11:47:41 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcer.h"

int			str_nbr(char *str, t_elems *elem)
{
	int		i;
	int		count;
	int		res;

	i = -1;
	count = 1;
	res = 0;
	elem->count = 0;
	while (str[++i] >= '0' && str[i] <= '9')
		elem->count++;
	if (i >= 5)
		return (10000);
	i = 0;
	elem->count = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * count + (str[i++] - 48);
		count = 10;
		elem->count++;
	}
	return (res);
}

void		sc_res_check(t_elems *elem)
{
	if (elem->map_y <= 0 || elem->map_x <= 0)
		errors(1);
	else if ((elem->map_y < 200 || elem->map_x < 320) &&
		(elem->map_y > 0 && elem->map_x > 0))
	{
		elem->map_y = 200;
		elem->map_x = 320;
	}
	else if (elem->map_y > 2048 || elem->map_x > 2560)
	{
		elem->map_y = 2048;
		elem->map_x = 2560;
	}
}

void		sc_res(t_elems *elem)
{
	int		i;

	i = 0;
	elem->r = skip_spaces(elem->r);
	if (elem->r[ft_strlen(elem->r) - 1] < '0' ||
		elem->r[ft_strlen(elem->r) - 1] > '9')
		errors(1);
	if (elem->r[i] <= '0' && elem->r[i] >= '9')
		errors(1);
	elem->map_x = str_nbr(elem->r + i, elem);
	i += elem->count;
	while (elem->r[i] <= 32)
		i++;
	if (elem->r[i] <= '0' && elem->r[i] >= '9')
		errors(1);
	elem->map_y = str_nbr(elem->r + i, elem);
	i += elem->count;
	if ((elem->r + i) && elem->r[i] > 32)
		errors(1);
	sc_res_check(elem);
}

void		count_sprites_2(t_elems *elem)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = -1;
	while (elem->map[++k])
	{
		j = -1;
		while (elem->map[k][++j])
			if (elem->map[k][j] == '2')
			{
				elem->spr[i].x = j + 0.5;
				elem->spr[i].y = k + 0.5;
				i++;
			}
	}
}

void		count_sprite(t_elems *elem)
{
	int		i;
	int		j;

	i = -1;
	elem->count = 0;
	while (elem->map[++i])
	{
		j = 0;
		while (elem->map[i][j])
			if (elem->map[i][j++] == '2')
				elem->count++;
	}
	elem->spr = (t_sprite *)ft_calloc(elem->count, sizeof(t_sprite));
	count_sprites_2(elem);
}
