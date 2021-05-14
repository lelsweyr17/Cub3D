/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 19:02:59 by lelsweyr          #+#    #+#             */
/*   Updated: 2021/02/08 19:48:30 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcer.h"

void		first_last_line(t_elems *elem, int len)
{
	int		i;

	i = 0;
	while (i < ft_strlen(elem->map[0]))
	{
		if (elem->map[0][i] != ' ' && elem->map[0][i] != '1')
			errors(6);
		i++;
	}
	i = 0;
	while (i < ft_strlen(elem->map[len - 1]))
	{
		if (elem->map[len - 1][i] != ' ' && elem->map[len - 1][i] != '1')
			errors(6);
		i++;
	}
}

void		null_check(char a)
{
	if (a != '0' && a != '1' && a != '2' &&
		a != 'N' && a != 'W' && a != 'E' && a != 'S')
		errors(6);
}

void		fill(int i, int j, t_elems *elem, int size)
{
	int		len;

	len = ft_strlen(elem->map[i]);
	while (++j < len)
		if (elem->map[i][j] == '0' || elem->map[i][j] == '2' ||
			elem->map[i][j] == 'N' || elem->map[i][j] == 'E' ||
			elem->map[i][j] == 'S' || elem->map[i][j] == 'W')
		{
			null_check(elem->map[i][j - 1]);
			null_check(elem->map[i][j + 1]);
			null_check(elem->map[i - 1][j - 1]);
			null_check(elem->map[i + 1][j + 1]);
			null_check(elem->map[i + 1][j - 1]);
			null_check(elem->map[i - 1][j + 1]);
			null_check(elem->map[i - 1][j]);
			null_check(elem->map[i + 1][j]);
		}
}

void		map_check(t_elems *elem, int len)
{
	int		i;
	int		j;

	i = 0;
	first_last_line(elem, len);
	while (i < len - 1)
	{
		j = 0;
		while (elem->map[i][j] <= 32)
			j++;
		fill(i, j - 1, elem, len);
		i++;
	}
}
