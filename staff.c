/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   staff.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 10:29:18 by tkiselev          #+#    #+#             */
/*   Updated: 2018/05/08 19:48:22 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		error(char error)
{
	ft_putstr("Error: ");
	error == ERROR_INVALID_FILE ? ft_putstr("invalid file.\n") : 0;
	error == ERROR_INVALID_QUANTITY_OF_ANTS ?
		ft_putstr("invalid quantity of ants.\n") : 0;
	error == ERROR_WITH_ROOM ? ft_putstr("not a valid room.\n") : 0;
	error == ERROR_NOT_UNIQUE_ROOM ? ft_putstr("not unique room.\n") : 0;
	error == ERROR_SECOND_START ? ft_putstr("several starts.\n") : 0;
	error == ERROR_SECOND_END ? ft_putstr("several ends.\n") : 0;
	error == ERROR_NOT_ENOUGH_INFO ?
		ft_putstr("not enough information.\n") : 0;
	error == ERROR_INVALID_LINK ? ft_putstr("invalid link.\n") : 0;
	error == ERROR_NO_SOLUTION ? ft_putstr("no solution.\n") : 0;
	exit(0);
}

void		clear_rooms(t_room *room)
{
	while (room)
	{
		room->visited = 0;
		room->level = 0;
		room->parent = NULL;
		room = room->next;
	}
}

int			length_way(t_way *way)
{
	int		l;

	l = -1;
	while (way)
	{
		way = way->next;
		l++;
	}
	return (l);
}
