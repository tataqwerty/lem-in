/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 10:29:18 by tkiselev          #+#    #+#             */
/*   Updated: 2018/06/14 17:49:05 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		enqueue(t_queue **queue, t_room *room)
{
	t_queue	*tmp;
	t_queue	*new;

	tmp = *queue;
	while (tmp && tmp->next)
		tmp = tmp->next;
	new = (t_queue *)malloc(sizeof(t_queue));
	new->next = NULL;
	new->room = room;
	new->room->iq = 1;
	if (!*queue)
		*queue = new;
	else
		tmp->next = new;
}

void		dequeue(t_queue **queue)
{
	t_queue	*tmp;

	if (!*queue)
		return ;
	tmp = (*queue)->next;
	(*queue)->room->iq = 0;
	free(*queue);
	*queue = tmp;
}

t_room		*get_room_from_queue(t_queue *queue, t_room *room_to_find)
{
	while (queue)
	{
		if (queue->room == room_to_find)
			return (queue->room);
		queue = queue->next;
	}
	return (NULL);
}

char		bfs(t_queue **queue)
{
	int		i;
	t_room	*tmp;

	if (!*queue)
		return (0);
	(*queue)->room->visited = 1;
	i = -1;
	while (++i < (*queue)->room->links_size)
	{
		if (!(*queue)->room->links[i]->visited &&
			!(*queue)->room->links[i]->iq &&
			!(*queue)->room->links[i]->used)
			enqueue(queue, (*queue)->room->links[i]);
		tmp = get_room_from_queue(*queue, (*queue)->room->links[i]);
		if (tmp && tmp->level == 0)
		{
			tmp->level = (*queue)->room->level + 1;
			tmp->parent = (*queue)->room;
			if (tmp->priority == END)
				return (1);
		}
	}
	dequeue(queue);
	return (bfs(queue));
}
