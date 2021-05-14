/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 18:04:24 by lelsweyr          #+#    #+#             */
/*   Updated: 2021/02/08 19:44:03 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARCER_H
# define PARCER_H

# include "minilibx_opengl/mlx.h"
# include "get_next_line.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>

typedef struct	s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct	s_tex_p
{
	float		x;
	float		y;
	float		step;
}				t_tex_p;

typedef struct	s_walls
{
	float		ray_x;
	float		ray_y;
	int			map_x;
	int			map_y;
	float		dir;
	float		ray_dir;
	float		wall_dist;
	int			line_heignt;
	int			draw_start;
	int			draw_end;
	float		grad;
}				t_walls;

typedef struct	s_params
{
	int			floor_color;
	int			c_color;
	char		*fl_color;
	char		*ceilling_color;
	int			n_side;
	int			e_side;
	int			s_side;
	int			w_side;
	int			cos;
}				t_params;

typedef struct	s_sprite
{
	float		x;
	float		y;
	float		ray;
	float		wall_dist;
	int			wall_height;
	float		alfa;
	float		left;
	float		right;
	float		pxl_start;
	float		pxl_end;
	float		pxl_up;
	float		pxl_down;
	float		pxl_step;
}				t_sprite;

typedef struct	s_tex
{
	int			w_no;
	int			h_no;
	int			w_ea;
	int			h_ea;
	int			w_so;
	int			h_so;
	int			w_we;
	int			h_we;
	int			w_spr;
	int			h_spr;
}				t_tex;

typedef	struct	s_move
{
	int			frwd:1;
	int			back:1;
	int			left:1;
	int			right:1;
	int			rt_left:1;
	int			rt_right:1;
	int			save:1;
}				t_move;

typedef struct	s_elems
{
	int			map_x;
	int			map_y;
	char		*r;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*s;
	char		*f;
	char		*c;
	char		**map;
	float		plr_x;
	float		plr_y;
	int			x;
	int			y;
	float		plr_a;
	void		*mlx;
	void		*win;
	void		*img;
	int			count;
	int			*sprites;
	int			*pxl_spr;
	float		*wall;
	int			up;
	int			save;
	float		delta;
	t_data		data;
	t_walls		walls;
	t_params	param;
	t_tex		tex;
	t_data		texts[5];
	t_tex_p		tex_p;
	t_sprite	*spr;
	t_move		move;
}				t_elems;

void			ft_parcer(t_elems *elem, int count);
void			ft_gnl(char *argv, t_list *st, t_elems *elem);
void			my_mlx_pp(t_elems *elem, int x, int y, int color);
void			map_3d(t_elems *elem);
int				map_mlx(t_elems *elem);
void			ft_plr(t_elems *elem);
void			floor_check(t_elems *elem);
void			ceilling_check(t_elems *elem);
int				str_nbr(char *str, t_elems *elem);
void			errors(int er);
void			textures(t_elems *elem);
unsigned		tex_color(t_data *tex, int x, int y);
void			draw_tex(t_elems *elem, int i);
int				check_params(char *map, int j);
int				ft_parcer_2(t_elems *elem, char *map, int j);
void			map_check(t_elems *elem, int len);
void			sc_res(t_elems *elem);
void			draw_3d(t_elems *elem, int i);
void			count_sprite(t_elems *elem);
void			sort_sprites(t_elems *elem);
void			part_spr(t_elems *elem, int i);
void			sprites(t_elems *elem, int i);
void			draw_sprite(t_elems *elem, int i, int pxl1, int pxl2);
void			draw_spr(int start, int end, t_elems *elem, int i);
int				exit_cube();
int				key_release(int keycode, t_elems *elem);
int				key_press(int keycode, t_elems *elem);
void			key_hook(t_elems *elem);
void			key_hook_2(t_elems *elem, float delta);
char			*skip_spaces(char *str);
void			del(void *a);
void			correct_file(char *file);
int				empty_line(char *con);
void			file_parcer(t_list *st, t_elems *elem);
void			bmp_scr(t_elems *elem, char *file);
void			init(t_elems *elem);
void			dest(t_elems *elem, int i, int j);

#endif
