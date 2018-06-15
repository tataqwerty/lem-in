/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 10:29:18 by tkiselev          #+#    #+#             */
/*   Updated: 2018/05/08 19:48:22 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room		*init_room(char **arr, char priority)
{
	t_room	*new;

	new = (t_room*)malloc(sizeof(t_room));
	new->x = ft_atoi(arr[1]);
	new->y = ft_atoi(arr[2]);
	new->level = 0;
	new->links_size = 0;
	new->priority = priority;
	new->used = 0;
	new->iq = 0;
	new->visited = 0;
	new->ants = 0;
	new->ant_id = 0;
	new->name = ft_strdup(arr[0]);
	new->parent = NULL;
	new->next = NULL;
	new->links = NULL;
	return (new);
}

void		room_push_front(t_room **room, char **arr, char priority)
{
	t_room	*new;

	new = init_room(arr, priority);
	if (!*room)
		*room = new;
	else
	{
		new->next = *room;
		*room = new;
	}
}

void		room_push_back(t_room **room, char **arr, char priority)
{
	t_room	*tmp;
	t_room	*new;

	tmp = *room;
	while (tmp)
	{
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	new = init_room(arr, priority);
	if (!tmp)
		*room = new;
	else
		tmp->next = new;
}

void		add_room(t_room **room, char *str, char priority)
{
	t_room	*tmp;
	char	**arr;
	int		x;
	int		y;

	tmp = *room;
	arr = ft_strsplit(str, ' ');
	x = ft_atoi(arr[1]);
	y = ft_atoi(arr[2]);
	while (tmp)
	{
		if (ft_strequ(tmp->name, arr[0]) || (tmp->x == x && tmp->y == y))
			error(ERROR_NOT_UNIQUE_ROOM);
		tmp = tmp->next;
	}
	if (priority == START)
		room_push_front(room, arr, priority);
	else
		room_push_back(room, arr, priority);
	y = -1;
	while (arr[++y])
		free(arr[y]);
	free(arr);
}

void		add_room_with_command(t_room **room, t_list **list, char *flag)
{
	if (ft_strequ((*list)->content, "##start"))
	{
		if ((*flag & 1) == 1)
			error(ERROR_SECOND_START);
		*flag = *flag | 1;
		if (!(*list = (*list)->next))
			error(ERROR_WITH_START_ROOM);
		skip_comments(list);
		if (!(*list) || !is_room((*list)->content))
			error(ERROR_WITH_START_ROOM);
		else
			add_room(room, (*list)->content, START);
		return ;
	}
	if ((*flag & 2) == 2)
		error(ERROR_SECOND_END);
	*flag = *flag | 2;
	if (!(*list = (*list)->next))
		error(ERROR_WITH_END_ROOM);
	skip_comments(list);
	if (!(*list) || !is_room((*list)->content))
		error(ERROR_WITH_END_ROOM);
	else
		add_room(room, (*list)->content, END);
}
