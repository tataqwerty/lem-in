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

void			error(char error)
{
	ft_putstr("Error: ");
	if (error == ERROR_INVALID_FILE)
		ft_putstr("invalid file.\n");
	else if (error == ERROR_INVALID_QUANTITY_OF_ANTS)
		ft_putstr("invalid quantity of ants.\n");
	else if (error == ERROR_HZ)
		ft_putstr("undefined error.\n");
	else if (error == ERROR_WITH_ROOM)
		ft_putstr("not valid room.\n");
	else if (error == ERROR_NOT_UNIQUE_ROOM)
		ft_putstr("not unique room.\n");
	else if (error == ERROR_SECOND_START)
		ft_putstr("several starts.\n");
	else if (error == ERROR_SECOND_END)
		ft_putstr("several ends.\n");
	else if (error == ERROR_NOT_ENOUGH_INFO)
		ft_putstr("not enough information.\n");
	else if (error == ERROR_INVALID_LINK)
		ft_putstr("invalid link.\n");
	else if (error == ERROR_INVALID_ORDER)
		ft_putstr("invalid order.\n");
	exit(0);
}

void			lines_to_list(t_str *s)
{
	char		*line;

	line = NULL;
	s->line_list = NULL;
	while (get_next_line(0, &line) > 0)
	{
		ft_list_pushback(&s->line_list, line);
		free(line);
	}
}

void			find_and_delete_list(t_list *main_list, t_list *tmp)
{
	t_list		*next;

	while (main_list->next && main_list->next != tmp)
		main_list = main_list->next;
	if (!main_list->next)
		return ;
	while (main_list->next)
	{
		next = main_list->next->next;
		free(main_list->next->content);
		main_list->next->content = NULL;
		free(main_list->next);
		main_list->next = next;
	}
}

void			clear_rooms(t_room *room)
{
	while (room)
	{
		room->visited = 0;
		room->level = 0;
		room->parent = NULL;
		room = room->next;
	}
}

unsigned int	length_way(t_way *way)
{
	int			l;

	l = -1;
	while (way)
	{
		way = way->next;
		l++;
	}
	return (l);
}
