/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceilling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 18:59:32 by lelsweyr          #+#    #+#             */
/*   Updated: 2021/02/08 11:43:25 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcer.h"

int			check_skip(char *c, int i, int n)
{
	int count;

	count = 0;
	while (c[i] <= 32)
		i++;
	if (c[i++] != ',')
		errors(n);
	while (c[i] <= 32)
		i++;
	if (c[i] < '0' && c[i] > '9')
		errors(n);
	while (c[i + count] >= '0' && c[i + count] <= '9')
		count++;
	if (!count)
		errors(n);
	return (i);
}

void		color_hex(int c, char *a, int m)
{
	int		n;
	int		i;

	n = c;
	i = 0;
	if (c < 0 || c > 255)
		errors(m);
	if (c < 10)
		a[i++] = 48;
	while (c >= 16)
	{
		c %= 16;
		if ((n /= 16) < 10)
			a[i++] = n + 48;
		else
			a[i++] = n + 55;
	}
	if (c < 10)
		a[i] = c + 48;
	else
		a[i] = c + 55;
}

int			hex_to_int(char *a, int c)
{
	int		i;
	int		p;

	i = 5;
	c = 0;
	p = 0;
	while (i >= 0)
		if (a[i] > 57)
			c += (a[i--] - 55) * pow(16, p++);
		else
		{
			c += (a[i--] - 48) * pow(16, p++);
		}
	return (c);
}

void		ceilling_check(t_elems *elem)
{
	int		i;
	int		r;
	int		g;
	int		b;

	i = 0;
	elem->param.ceilling_color = (char *)ft_calloc(8, sizeof(char));
	elem->c = skip_spaces(elem->c);
	r = str_nbr(elem->c, elem);
	if ((i += elem->count) == 0)
		errors(5);
	i = check_skip(elem->c, i, 5);
	g = str_nbr(elem->c + i, elem);
	i += elem->count;
	i = check_skip(elem->c, i, 5);
	b = str_nbr(elem->c + i, elem);
	i += elem->count;
	if (elem->c[i])
		errors(5);
	color_hex(r, elem->param.ceilling_color, 5);
	color_hex(g, elem->param.ceilling_color + 2, 5);
	color_hex(b, elem->param.ceilling_color + 4, 5);
	elem->param.c_color = hex_to_int(elem->param.ceilling_color,
	elem->param.c_color);
}

void		floor_check(t_elems *elem)
{
	int		i;
	int		r;
	int		g;
	int		b;

	i = 0;
	elem->param.fl_color = (char *)ft_calloc(8, sizeof(char));
	elem->f = skip_spaces(elem->f);
	r = str_nbr(elem->f, elem);
	if ((i += elem->count) == 0)
		errors(4);
	i = check_skip(elem->f, i, 4);
	g = str_nbr(elem->f + i, elem);
	i += elem->count;
	i = check_skip(elem->f, i, 4);
	b = str_nbr(elem->f + i, elem);
	i += elem->count;
	if (elem->f[i])
		errors(4);
	color_hex(r, elem->param.fl_color, 4);
	color_hex(g, elem->param.fl_color + 2, 4);
	color_hex(b, elem->param.fl_color + 4, 4);
	elem->param.floor_color = hex_to_int(elem->param.fl_color,
	elem->param.floor_color);
}
