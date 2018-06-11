/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 10:29:18 by tkiselev          #+#    #+#             */
/*   Updated: 2018/05/08 19:48:22 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

#include <stdio.h>

void	error(char error)
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
	exit (0);
}

void	lines_to_list(t_str *s)
{
	char	*line;

	line = NULL;
	s->line_list = NULL;
	while (get_next_line(0, &line) > 0)
	{
		ft_list_pushback(&s->line_list, line);
		free(line);
	}
}


char	is_command(char *str)
{
	if (ft_strequ(str, "##start") || ft_strequ(str, "##end"))
		return (1);
	return (0);
}

void		get_ants_counter(int *ants, t_list **list)
{
	int		i;

	i = 0;
	while (*list)
	{
		if (((char*)(*list)->content)[0] >= '0'
			&& ((char*)(*list)->content)[0] <= '9')
			break ;
		else if (is_command((*list)->content))
			error(ERROR_INVALID_ORDER);
		else if (((char*)(*list)->content)[0] != '#')
			error(ERROR_INVALID_FILE);
		*list = (*list)->next;
	}
	if (!*list)
		error(ERROR_INVALID_QUANTITY_OF_ANTS);
	while (((char*)(*list)->content)[i] != '\0' &&
		((char*)(*list)->content)[i] >= '0' &&
		((char*)(*list)->content)[i] <= '9')
		*ants = *ants * 10 + ((char*)(*list)->content)[i++] - 48;
	if (i == 0 || *ants == 0 || ((char*)(*list)->content)[i] != '\0')
		error(ERROR_INVALID_QUANTITY_OF_ANTS);
	*list = (*list)->next;
}

char	is_room(char *str)
{
	char	flag;
	int		i;

	if (!str || str[0] == 'L' || str[0] == '#')
		return (0);
	flag = 0;
	i = 0;
	while (str[i] != '\0' && str[i] > 32 && str[i] < 127
		&& str[i] != '-' && (flag = 1))
		i++;
	if (flag != 1 || str[i++] != ' ')
		return (0);
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9' && (flag = 2))
		i++;
	if (flag != 2 || str[i++] != ' ')
		return (0);
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9' && (flag = 3))
		i++;
	if (flag != 3 || str[i] != '\0')
		return (0);
	return (1);
}

char	is_link(char *s)
{
	int		i;
	char	flag;

	if (!s || s[0] == 'L' || s[0] == '#')
		return (0);
	i = 0;
	flag = 0;
	while (s[i] > 32 && s[i] < 127 && s[i] != '-' && (flag = 1))
		i++;
	if (flag != 1 || s[i++] != '-' || s[i] == 'L' || s[i] == '#')
		return (0);
	while (s[i] > 32 && s[i] < 127 && s[i] != '-' && (flag = 2))
		i++;
	if (flag != 2 || s[i] != '\0')
		return (0);
	return (1);
}

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
	new->name = ft_strdup(arr[0]);
	new->parent = NULL;
	new->next = NULL;
	new->links = NULL;
	return (new);
}

void	room_push_front(t_room **room, char **arr, char priority)
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

void	room_push_back(t_room **room, char **arr, char priority)
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

void	add_room(t_room **room, char *str, char priority)
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

void	add_room_with_command(t_room **room, t_list **list, char *flag)
{
	if (ft_strequ((*list)->content, "##start"))
	{
		if ((*flag & 1) == 1)
			error(ERROR_SECOND_START);
		*flag = *flag | 1;
		if (!(*list = (*list)->next) || !is_room((*list)->content))
			error(ERROR_WITH_ROOM);
		else
			add_room(room, (*list)->content, START);
	}
	else if (ft_strequ((*list)->content, "##end"))
	{
		if ((*flag & 2) == 2)
			error(ERROR_SECOND_END);
		*flag = *flag | 2;
		if (!(*list = (*list)->next) || !is_room((*list)->content))
			error(ERROR_WITH_ROOM);
		else
			add_room(room, (*list)->content, END);
	}
}

void	get_rooms(t_str *s, t_list **list)
{
	char	flag;

	flag = 0;
	while (*list)
	{
		if (is_room((*list)->content))
			add_room(&s->room, (*list)->content, 0);
		else if (is_command((*list)->content))
			add_room_with_command(&s->room, list, &flag);
		else if (is_link((*list)->content))
		{
			if (flag != 3)
				error(ERROR_NOT_ENOUGH_INFO);
			else
				return ;
		}
		else if (((char*)(*list)->content)[0] != '#')
			error(ERROR_INVALID_FILE);
		*list = (*list)->next;
	}
	error(ERROR_NOT_ENOUGH_INFO);
}

char		apply_link(t_room ***links, t_room *room, int *size)
{
	t_room	**new_arr;
	int		i;

	i = -1;
	while (++i < *size)
	{
		if (ft_strequ((*links)[i]->name, room->name))
			return (0);
	}
	new_arr = (t_room **)malloc(sizeof(t_room *) * (*size + 1));
	i = -1;
	while (++i < *size)
		new_arr[i] = (*links)[i];
	new_arr[i] = room;
	if (*size > 0)
		free(*links);
	*size += 1;
	*links = new_arr;
	return (0);
}

char		connect_links(t_room *room1, t_room *room2)
{
	char	error;

	if (!room1 || !room2 || ft_strequ(room1->name, room2->name))
		return (ERROR_INVALID_LINK);
	if ((error = apply_link(&room1->links, room2, &room1->links_size)) != 0 ||
		(error = apply_link(&room2->links, room1, &room2->links_size)) != 0)
		return (error);
	return (0);
}

char		find_place_n_connect_links(t_room **head, char *link)
{
	char	**arr;
	t_room	*tmp1;
	t_room	*tmp2;
	int		i;

	tmp1 = *head;
	tmp2 = *head;
	arr = ft_strsplit(link, '-');
	while (tmp1)
	{
		if (ft_strequ(tmp1->name, arr[0]))
			break ;
		tmp1 = tmp1->next;
	}
	while (tmp2)
	{
		if (ft_strequ(tmp2->name, arr[1]))
			break ;
		tmp2 = tmp2->next;
	}
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (connect_links(tmp1, tmp2));
}

char		get_links(t_str *s, t_list **list)
{
	char	error;

	if ((error = find_place_n_connect_links(&s->room, (*list)->content)) != 0)
		return (error);
	*list = (*list)->next;
	while (*list)
	{
		if (is_link((*list)->content))
		{
			if ((error = find_place_n_connect_links(&s->room, (*list)->content)) != 0)
				return (error);
		}
		else if (((char*)(*list)->content)[0] != '#')
			return (ERROR_INVALID_ORDER);
		*list = (*list)->next;
	}
	return (0);
}

void	find_and_delete_list(t_list *main_list, t_list *tmp)
{
	t_list	*next;

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

char		parsing(t_str *s)
{
	t_list	*tmp;
	char	err;

	s->ants_counter = 0;
	s->room = NULL;
	s->ant = NULL;
	lines_to_list(s);
	tmp = s->line_list;
	get_ants_counter(&s->ants_counter, &tmp);
	get_rooms(s, &tmp);
	err = get_links(s, &tmp);
	if (err != 0)
		find_and_delete_list(s->line_list, tmp);
	return (err);
}

// ALGORITHM

void		enqueue(t_queue **queue, t_room *room)
{
	t_queue	*tmp;
	t_queue	*new;

	tmp = *queue;
	while (tmp)
	{
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
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

char	BFS(t_queue **queue)
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
	return (BFS(queue));
}

void	delete_ways(t_ways ***ways, int *ways_size)
{
	t_way	*next;
	t_way	*current;
	int		i;

	i = -1;
	while (++i < *ways_size)
	{
		current = (*ways)[i]->way;
		while (current)
		{
			next = current->next;
			free(current);
			current = next;
		}
		free((*ways)[i]);
		(*ways)[i] = NULL;
	}
	if (*ways_size > 0)
		free(*ways);
	*ways = NULL;
	*ways_size = 0;
}

int		length_way(t_way *way)
{
	int l;

	l = -1;
	while (way)
	{
		way = way->next;
		l++;
	}
	return (l);
}

void	remalloc_ways(t_ways ***ways, t_way *new_way, int *ways_size)
{
	t_ways		**new_ways;
	int			i;

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

void	pushfront(t_way **way, t_room *room)
{
	t_way		*new;

	new = (t_way *)malloc(sizeof(t_way));
	new->next = *way;
	new->room = room;
	*way = new;
}

t_way		*create_way(t_room *end_room)
{
	t_way	*new_way;

	new_way = NULL;
	pushfront(&new_way, end_room);
	end_room = end_room->parent;
	while (end_room && end_room->priority != START)
	{
		pushfront(&new_way, end_room);
		end_room->used = 1;
		end_room = end_room->parent;
	}
	pushfront(&new_way, end_room);
	return (new_way);
}

void	clear_rooms(t_room *room)
{
	while (room)
	{
		room->visited = 0;
		room->level = 0;
		room->parent = NULL;
		room = room->next;
	}
}

void	generate_ways(t_str *s)
{
	t_queue		*queue;
	t_room		*end_room;

	s->ways = NULL;
	s->ways_size = 0;
	queue = NULL;
	enqueue(&queue, s->room);
	end_room = s->room;
	while (end_room && end_room->priority != END)
		end_room = end_room->next;
	while (BFS(&queue))
	{
		if (end_room->level == 1)
		{
			delete_ways(&s->ways, &s->ways_size);
			remalloc_ways(&s->ways, create_way(end_room), &s->ways_size);
			return ;
		}
		remalloc_ways(&s->ways, create_way(end_room), &s->ways_size);
		clear_rooms(s->room);
		while (queue)
			dequeue(&queue);
		enqueue(&queue, s->room);
	}
}

void	output(t_str *s)
{
	t_list	*tmp;

	tmp = s->line_list;
	while (tmp)
	{
		ft_putendl(tmp->content);
		tmp = tmp->next;
	}
	
	int i = -1;
	t_way	*tmp2;
	while (++i < s->ways_size)
	{
		printf("\nPATH no: %d\n", i + 1);
		tmp2 = s->ways[i]->way;
		while (tmp2)
		{
			ft_putendl(tmp2->room->name);
			tmp2 = tmp2->next;
		}
	}
}

int			main(void)
{
	t_str	*s;
	char	err;

	s = (t_str*)malloc(sizeof(t_str));
	err = parsing(s);
	generate_ways(s);
	if (!s->ways)
		error(err);
	// output(s);
	return (0);
}
