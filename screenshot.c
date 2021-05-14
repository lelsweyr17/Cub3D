/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 19:04:15 by lelsweyr          #+#    #+#             */
/*   Updated: 2021/02/08 19:24:01 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcer.h"

void				dest(t_elems *elem, int i, int j)
{
	if (elem->map[i][j] == 'S')
		elem->plr_a = M_PI / 2;
	else if (elem->map[i][j] == 'W')
		elem->plr_a = M_PI;
	else if (elem->map[i][j] == 'N')
		elem->plr_a = M_PI * 1.5;
	else if (elem->map[i][j] == 'E')
		elem->plr_a = 0;
}

void				header(unsigned char *head1, unsigned char *head2,
					t_elems *elem)
{
	unsigned		n;

	n = 54 + elem->map_x * elem->map_y * elem->data.bits_per_pixel / 8;
	head1[0] = 'B';
	head1[1] = 'M';
	head1[2] = (unsigned char)(n);
	head1[3] = (unsigned char)(n >> 8);
	head1[4] = (unsigned char)(n >> 16);
	head1[5] = (unsigned char)(n >> 24);
	head1[10] = (unsigned char)(54);
	head2[0] = (unsigned char)(40);
	head2[4] = (unsigned char)(elem->map_x);
	head2[5] = (unsigned char)(elem->map_x >> 8);
	head2[6] = (unsigned char)(elem->map_x >> 16);
	head2[7] = (unsigned char)(elem->map_x >> 24);
	head2[8] = (unsigned char)(-elem->map_y);
	head2[9] = (unsigned char)(-elem->map_y >> 8);
	head2[10] = (unsigned char)(-elem->map_y >> 16);
	head2[11] = (unsigned char)(-elem->map_y >> 24);
	head2[12] = (unsigned char)(1);
	head2[14] = (unsigned char)(32);
}

void				bmp_scr(t_elems *elem, char *file)
{
	int				fd;
	int				i;
	unsigned		size;
	unsigned char	head1[14];
	unsigned char	head2[40];

	i = -1;
	if (!(fd = open(file, O_RDWR | O_CREAT, 0755)))
		errors(11);
	ft_bzero(head1, 14);
	ft_bzero(head2, 40);
	header(head1, head2, elem);
	write(fd, head1, 14);
	write(fd, head2, 40);
	size = elem->map_x * elem->data.bits_per_pixel / 8;
	while (++i < elem->map_y)
		write(fd, elem->data.addr + i * elem->data.line_length, size);
}
