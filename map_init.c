/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 18:04:29 by lelsweyr          #+#    #+#             */
/*   Updated: 2021/02/08 19:38:09 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcer.h"

void		ft_plr(t_elems *elem)
{
	int		i;
	int		j;
	int		count;

	count = 0;
	i = -1;
	j = -1;
	while (elem->map[++i])
	{
		while (elem->map[i][++j])
			if (elem->map[i][j] == 'N' || elem->map[i][j] == 'W' ||
				elem->map[i][j] == 'S' || elem->map[i][j] == 'E')
			{
				dest(elem, i, j);
				elem->plr_x = j;
				elem->plr_y = i;
				count++;
			}
		j = 0;
	}
	if (count == 0)
		errors(7);
	else if (count > 1)
		errors(8);
}

void		full_map(t_elems *elem, int count, t_list *tmp)
{
	int		i;

	i = -1;
	elem->map = (char **)ft_calloc(count + 1, sizeof(char *));
	while (count--)
	{
		elem->map[++i] = tmp->content;
		tmp = tmp->next;
	}
}

t_list		*count_params(t_list *tmp, t_elems *elem)
{
	int		i;
	int		j;
	int		count;

	i = 0;
	j = 0;
	count = 0;
	while (tmp && count != 8)
	{
		if (ft_strlen(tmp->content = skip_spaces(tmp->content)) > 0)
			count += 1;
		j += check_params(tmp->content, 0);
		i += ft_parcer_2(elem, tmp->content, 0);
		tmp = tmp->next;
	}
	if (j != 255)
		errors(3);
	return (tmp);
}

int			map_counter(t_list *tmp)
{
	int		i;
	t_list	*t;

	i = 0;
	while (tmp && empty_line(tmp->content) == 1)
	{
		i++;
		tmp = tmp->next;
	}
	while (tmp)
	{
		if (empty_line(tmp->content) == 1)
			errors(6);
		t = tmp->content;
		free(t);
		tmp = tmp->next;
	}
	return (i);
}

void		file_parcer(t_list *st, t_elems *elem)
{
	int		i;
	t_list	*tmp;
	t_list	*t;
	t_list	*start;

	i = 0;
	if (!(tmp = count_params(st, elem)))
		errors(3);
	while (tmp && empty_line(tmp->content) == 0)
	{
		t = tmp->content;
		free(t);
		tmp = tmp->next;
	}
	start = tmp;
	i = map_counter(tmp);
	full_map(elem, i, start);
	ft_lstclear(&st, del);
	ft_parcer(elem, i);
}
