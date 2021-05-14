/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 15:29:41 by lelsweyr          #+#    #+#             */
/*   Updated: 2021/02/08 19:06:29 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcer.h"

void		errors(int er)
{
	if (er == 1)
		write(1, "Error: invalid screen resolution\n", 34);
	else if (er == 2)
		write(1, "Error: texture file isn't found\n", 33);
	else if (er == 3)
		write(1, "Error: count of parameters of map isn't correct\n", 49);
	else if (er == 4)
		write(1, "Error: floor color isn't correct\n", 34);
	else if (er == 5)
		write(1, "Error: ceilling color isn't correct\n", 37);
	else if (er == 6)
		write(1, "Error: invalid map\n", 20);
	else if (er == 7)
		write(1, "Error: player is not found\n", 28);
	else if (er == 8)
		write(1, "Error: several players, it's have to be only one!\n", 51);
	else if (er == 9)
		write(1, "Error: file resolution isn't correct\n", 38);
	else if (er == 10)
		write(1, "Error: map file not fount\n", 27);
	else if (er == 11)
		write(1, "Error: screenshot file can't be created\n", 41);
	else if (er == 12)
		write(1, "Error: argument --save isn't correct\n", 38);
	exit(0);
}

void		correct_file(char *file)
{
	int		len;

	len = ft_strlen(file);
	len -= 4;
	if (file[len] != '.')
		errors(9);
	if (file[len + 1] != 'c')
		errors(9);
	if (file[len + 2] != 'u')
		errors(9);
	if (file[len + 3] != 'b')
		errors(9);
}

void		del(void *a)
{
	a = NULL;
	free(a);
}

int			empty_line(char *con)
{
	int		i;

	i = -1;
	while (con[++i])
		if (con[i] > 32)
			return (1);
	return (0);
}

void		ft_gnl(char *argv, t_list *st, t_elems *elem)
{
	int		fd;
	char	*line;

	correct_file(argv);
	fd = open(argv, O_RDONLY);
	line = NULL;
	st = NULL;
	while (get_next_line(fd, &line))
		ft_lstadd_back(&st, ft_lstnew(line));
	ft_lstadd_back(&st, ft_lstnew(line));
	file_parcer(st, elem);
}
