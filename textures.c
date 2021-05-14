/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 18:03:56 by lelsweyr          #+#    #+#             */
/*   Updated: 2021/02/06 18:13:27 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcer.h"

unsigned		tex_color(t_data *tex, int x, int y)
{
	char		*dst;
	unsigned	color;

	dst = tex->addr + (y * tex->line_length +
	x * (tex->bits_per_pixel / 8));
	color = *(unsigned int*)dst;
	return (color);
}

void			draw_3d(t_elems *elem, int i)
{
	int			y;

	y = -1;
	while (++y < elem->walls.draw_start)
		my_mlx_pp(elem, i, y, elem->param.c_color);
	y += elem->walls.line_heignt;
	while (y < elem->map_y)
		my_mlx_pp(elem, i, y++, elem->param.floor_color);
}

void			textures(t_elems *elem)
{
	elem->texts[0].img = mlx_xpm_file_to_image(elem->mlx, elem->s,
	&elem->tex.w_spr, &elem->tex.h_spr);
	elem->texts[0].addr = mlx_get_data_addr(elem->texts[0].img,
	&elem->texts[0].bits_per_pixel, &elem->texts[0].line_length,
	&elem->texts[0].endian);
	elem->texts[1].img = mlx_xpm_file_to_image(elem->mlx, elem->no,
	&elem->tex.w_no, &elem->tex.h_no);
	elem->texts[1].addr = mlx_get_data_addr(elem->texts[1].img,
	&elem->texts[1].bits_per_pixel, &elem->texts[1].line_length,
	&elem->texts[1].endian);
	elem->texts[2].img = mlx_xpm_file_to_image(elem->mlx, elem->ea,
	&elem->tex.w_ea, &elem->tex.h_ea);
	elem->texts[2].addr = mlx_get_data_addr(elem->texts[2].img,
	&elem->texts[2].bits_per_pixel, &elem->texts[2].line_length,
	&elem->texts[2].endian);
	elem->texts[3].img = mlx_xpm_file_to_image(elem->mlx, elem->so,
	&elem->tex.w_so, &elem->tex.h_so);
	elem->texts[3].addr = mlx_get_data_addr(elem->texts[3].img,
	&elem->texts[3].bits_per_pixel, &elem->texts[3].line_length,
	&elem->texts[3].endian);
	elem->texts[4].img = mlx_xpm_file_to_image(elem->mlx, elem->we,
	&elem->tex.w_we, &elem->tex.h_we);
	elem->texts[4].addr = mlx_get_data_addr(elem->texts[4].img,
	&elem->texts[4].bits_per_pixel, &elem->texts[4].line_length,
	&elem->texts[4].endian);
}

void			draw_tex_init(t_elems *elem, float *dy, float *end, float *side)
{
	elem->tex_p.x = elem->tex_p.x - (int)elem->tex_p.x;
	elem->tex_p.y = elem->tex_p.y - (int)elem->tex_p.y;
	elem->tex_p.step = (float)64 / elem->walls.line_heignt;
	elem->tex_p.x = elem->tex_p.x * 64;
	elem->tex_p.y = elem->tex_p.y * 64;
	*dy = 0;
	*end = 64;
	*side = (elem->param.n_side || elem->param.s_side ?
	elem->tex_p.x : elem->tex_p.y);
}

void			draw_tex(t_elems *elem, int i)
{
	int			start;
	float		dy;
	float		end;
	float		side;

	draw_tex_init(elem, &dy, &end, &side);
	start = elem->walls.draw_start;
	if (elem->walls.line_heignt > elem->map_y)
	{
		dy = (elem->walls.line_heignt / 2 - elem->map_y / 2) * elem->tex_p.step;
		end = 64 - ((elem->walls.line_heignt / 2 - elem->map_y / 2) *
		elem->tex_p.step);
	}
	while (dy < end)
	{
		if (elem->param.n_side)
			my_mlx_pp(elem, i, start++, tex_color(&elem->texts[1], side, dy));
		if (elem->param.e_side)
			my_mlx_pp(elem, i, start++, tex_color(&elem->texts[2], side, dy));
		if (elem->param.s_side)
			my_mlx_pp(elem, i, start++, tex_color(&elem->texts[3], side, dy));
		if (elem->param.w_side)
			my_mlx_pp(elem, i, start++, tex_color(&elem->texts[4], side, dy));
		dy += elem->tex_p.step;
	}
}
