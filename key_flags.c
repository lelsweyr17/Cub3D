/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 18:21:37 by lelsweyr          #+#    #+#             */
/*   Updated: 2021/02/07 20:45:48 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcer.h"

void			key_hook_2(t_elems *elem, float delta)
{
	if (elem->move.left && elem->map[(int)(elem->plr_y + 0.2 * sin(delta))]
		[(int)(elem->plr_x + 0.2 * cos(delta))] != '1' &&
		elem->map[(int)(elem->plr_y + 0.5 * sin(delta))]
		[(int)(elem->plr_x + 0.5 * cos(delta))] != '2')
	{
		elem->plr_y += 0.05 * sin(delta);
		elem->plr_x += 0.05 * cos(delta);
	}
	if (elem->move.right && elem->map[(int)(elem->plr_y - 0.2 * sin(delta))]
		[(int)(elem->plr_x - 0.2 * cos(delta))] != '1' &&
		elem->map[(int)(elem->plr_y - 0.5 * sin(delta))]
		[(int)(elem->plr_x - 0.5 * cos(delta))] != '2')
	{
		elem->plr_y -= 0.05 * sin(delta);
		elem->plr_x -= 0.05 * cos(delta);
	}
	if (elem->move.rt_left)
		elem->plr_a -= 0.05;
	if (elem->move.rt_right)
		elem->plr_a += 0.05;
}

void			key_hook(t_elems *elem)
{
	float		delta;
	float		plr;

	plr = elem->plr_a;
	delta = plr - M_PI / 2;
	if (elem->move.frwd && elem->map[(int)(elem->plr_y + 0.2 * sin(plr))]
		[(int)(elem->plr_x + 0.2 * cos(plr))] != '1' &&
		elem->map[(int)(elem->plr_y + 0.5 * sin(plr))]
		[(int)(elem->plr_x + 0.5 * cos(plr))] != '2')
	{
		elem->plr_y += 0.1 * sin(plr);
		elem->plr_x += 0.1 * cos(plr);
	}
	if (elem->move.back && elem->map[(int)(elem->plr_y - 0.2 * sin(plr))]
		[(int)(elem->plr_x - 0.2 * cos(elem->plr_a))] != '1' &&
		elem->map[(int)(elem->plr_y - 0.5 * sin(plr))]
		[(int)(elem->plr_x - 0.5 * cos(plr))] != '2')
	{
		elem->plr_y -= 0.1 * sin(plr);
		elem->plr_x -= 0.1 * cos(plr);
	}
	key_hook_2(elem, delta);
}

int				key_press(int keycode, t_elems *elem)
{
	if (keycode == 13)
		elem->move.frwd = 1;
	if (keycode == 1)
		elem->move.back = 1;
	if (keycode == 0)
		elem->move.left = 1;
	if (keycode == 2)
		elem->move.right = 1;
	if (keycode == 123)
		elem->move.rt_left = 1;
	if (keycode == 124)
		elem->move.rt_right = 1;
	if (elem->move.rt_left && elem->move.rt_right && (elem->move.rt_left = 0))
		elem->move.rt_right = 0;
	if (elem->move.frwd && elem->move.back && (elem->move.back = 0))
		elem->move.frwd = 0;
	if (elem->move.left && elem->move.right && (elem->move.right = 0))
		elem->move.left = 0;
	if (keycode == 259)
		elem->move.save = 1;
	if (keycode == 53)
		exit(0);
	return (0);
}

int				key_release(int keycode, t_elems *elem)
{
	if (keycode == 13)
		elem->move.frwd = 0;
	if (keycode == 1)
		elem->move.back = 0;
	if (keycode == 0)
		elem->move.left = 0;
	if (keycode == 2)
		elem->move.right = 0;
	if (keycode == 123)
		elem->move.rt_left = 0;
	if (keycode == 124)
		elem->move.rt_right = 0;
	if (keycode == 259)
		elem->move.rt_right = 0;
	return (0);
}

int				exit_cube(void)
{
	exit(0);
}
