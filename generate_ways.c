/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_ways.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 10:29:18 by tkiselev          #+#    #+#             */
/*   Updated: 2018/05/08 19:48:22 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		remalloc_ways(t_ways ***ways, t_way *new_way, int *ways_size)
{
	t_ways	**new_ways;
	int		i;

	i = -1;
	new_ways = (t_ways **)malloc(sizeof(t_ways *) * (*ways_size + 1));
	while (++i < *ways_size)
		new_ways[i] = (*ways)[i];
	new_ways[i] = (t_ways *)malloc(sizeof(t_ways));
	new_ways[i]->way = new_way;
	new_ways[i]->length = length_way(new_way);
	if (*ways_size > 0)
		free(*ways);
	(*ways_size)++;
	*ways = new_ways;
}

void		pushback(t_way **way, t_room *room)
{
	t_way	*new;
	t_way	*tmp;

	new = (t_way *)malloc(sizeof(t_way));
	new->next = NULL;
	new->room = room;
	tmp = *way;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (!*way)
		*way = new;
	else
		tmp->next = new;
}

t_way		*create_way(t_room *end_room)
{
	t_way	*new_way;

	new_way = NULL;
	pushback(&new_way, end_room);
	end_room = end_room->parent;
	while (end_room && end_room->priority != START)
	{
		pushback(&new_way, end_room);
		end_room->used = 1;
		end_room = end_room->parent;
	}
	pushback(&new_way, end_room);
	return (new_way);
}

void		generate_ways(t_str *s)
{
	t_queue	*queue;
	t_room	*end_room;

	s->ways = NULL;
	s->ways_size = 0;
	queue = NULL;
	enqueue(&queue, s->room);
	end_room = s->room;
	while (end_room && end_room->priority != END)
		end_room = end_room->next;
	while (bfs(&queue))
	{
		while (queue)
			dequeue(&queue);
		remalloc_ways(&s->ways, create_way(end_room), &s->ways_size);
		if (end_room->level == 1)
			return ;
		clear_rooms(s->room);
		enqueue(&queue, s->room);
	}
}
