/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 18:44:10 by lelsweyr          #+#    #+#             */
/*   Updated: 2021/02/08 11:43:47 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcer.h"

int		ft_parcer_2(t_elems *elem, char *map, int j)
{
	if (map[j] == 'R' && map[j + 1] <= 32)
		elem->r = &map[j + 2];
	else if (map[j] == 'N' && map[j + 1] == 'O' && map[j + 2] <= 32)
		elem->no = &map[j + 3];
	else if (map[j] == 'S' && map[j + 1] == 'O' && map[j + 2] <= 32)
		elem->so = &map[j + 3];
	else if (map[j] == 'W' && map[j + 1] == 'E' && map[j + 2] <= 32)
		elem->we = &map[j + 3];
	else if (map[j] == 'E' && map[j + 1] == 'A' && map[j + 2] <= 32)
		elem->ea = &map[j + 3];
	else if (map[j] == 'S' && map[j + 1] <= 32)
		elem->s = &map[j + 2];
	else if (map[j] == 'F' && map[j + 1] <= 32)
		elem->f = &map[j + 2];
	else if (map[j] == 'C' && map[j + 1] <= 32)
		elem->c = &map[j + 2];
	else
		return (0);
	return (1);
}

char	*skip_spaces(char *str)
{
	int i;
	int j;
	int len;

	i = 0;
	j = 0;
	len = ft_strlen(str) - 1;
	while (str[i] <= 32)
		i++;
	while (str[len] <= 32)
		len--;
	while (i <= len)
		str[j++] = str[i++];
	str[j] = 0;
	return (str);
}

void	texture_check(t_elems *elem)
{
	int fd;

	elem->no = skip_spaces(elem->no);
	elem->so = skip_spaces(elem->so);
	elem->we = skip_spaces(elem->we);
	elem->ea = skip_spaces(elem->ea);
	elem->s = skip_spaces(elem->s);
	if ((fd = open(elem->no, O_RDONLY)) < 0)
		errors(2);
	if ((fd = open(elem->so, O_RDONLY)) < 0)
		errors(2);
	if ((fd = open(elem->we, O_RDONLY)) < 0)
		errors(2);
	if ((fd = open(elem->ea, O_RDONLY)) < 0)
		errors(2);
	if ((fd = open(elem->s, O_RDONLY)) < 0)
		errors(2);
	close(fd);
}

int		check_params(char *map, int j)
{
	if (map[0] == 'R' && map[1] <= 32)
		j += 1;
	else if (map[0] == 'N' && map[1] == 'O' && map[2] <= 32)
		j += 2;
	else if (map[0] == 'S' && map[1] == 'O' && map[2] <= 32)
		j += 4;
	else if (map[0] == 'W' && map[1] == 'E' && map[2] <= 32)
		j += 8;
	else if (map[0] == 'E' && map[1] == 'A' && map[2] <= 32)
		j += 16;
	else if (map[0] == 'S' && map[1] <= 32)
		j += 32;
	else if (map[0] == 'F' && map[1] <= 32)
		j += 64;
	else if (map[0] == 'C' && map[1] <= 32)
		j += 128;
	return (j);
}

void	ft_parcer(t_elems *elem, int count)
{
	int i;
	int j;

	i = 0;
	j = 0;
	elem->count = 0;
	sc_res(elem);
	texture_check(elem);
	floor_check(elem);
	ceilling_check(elem);
	map_check(elem, count);
}
