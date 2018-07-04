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

void			skip_comments(t_list **list)
{
	while (*list)
	{
		if (is_command((*list)->content))
			break ;
		else if ((*list)->content_size >= 1 &&
			((char*)(*list)->content)[0] == '#')
			*list = (*list)->next;
		else
			break ;
	}
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

int				length_way(t_way *way)
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
