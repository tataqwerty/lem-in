#include "lem-in.h"

void	line_list_del(t_list **head)
{
	t_list *tmp;

	if (!head || !*head)
		return ;
	while (*head)
	{
		tmp = (*head)->next;
		free((*head)->content);
		free(*head);
		*head = tmp;
	}
}

// void	room_list_del(t_room **room)
// {

// }

void	error_management(char error)
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
	else if (error == ERROR_S_START)
		ft_putstr("several starts.\n");
	else if (error == ERROR_S_END)
		ft_putstr("several ends.\n");
	else if (error == ERROR_NOT_ENOUGH_INFO)
		ft_putstr("not enough information.\n");
	else if (error == ERROR_NOT_UNIQUE_LINK)
		ft_putstr("not unique link.\n");
	else if (error == ERROR_INVALID_LINK)
		ft_putstr("invalid link.\n");
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

char		get_ants_counter(int *ants, t_list **list)
{
	char	*str;
	int		i;

	i = 0;
	if (!list || !*list || !(*list)->content)
		return (ERROR_INVALID_FILE);
	str = (*list)->content;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
		*ants = *ants * 10 + str[i++] - 48;
	if (i == 0 || *ants == 0 || str[i] != '\0')
		return (ERROR_INVALID_QUANTITY_OF_ANTS);
	*list = (*list)->next;
	return (0);
}

char	is_room(char *str)
{
	char	flag;
	int		i;

	if (!str || str[0] == 'L' || str[0] == '#')
		return (0);
	flag = 0;
	i = 0;
	while (str[i] != '\0' && str[i] > 32 && str[i] < 127 && str[i] != '-' && (flag = 1))
		i++;
	if (flag == 0 || str[i++] != ' ')
		return (0);
	flag = 0;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9' && (flag = 1))
		i++;
	if (flag == 0 || str[i++] != ' ')
		return (0);
	flag = 0;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9' && (flag = 1))
		i++;
	if (flag == 0 || str[i] != '\0')
		return (0);
	return (1);
}

char	is_command(char *str)
{
	if (ft_strequ(str, "##start") || ft_strequ(str, "##end"))
		return (1);
	return (0);
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
	if (flag == 0 || s[i++] != '-' || s[i] == 'L' || s[i] == '#')
		return (0);
	flag = 0;
	while (s[i] > 32 && s[i] < 127 && s[i] != '-' && (flag = 1))
		i++;
	if (flag == 0 || s[i] != '\0')
		return (0);
	return (1);
}

void	room_push_front(t_room **room, char **arr, char priority)
{
	t_room	*new;

	new = (t_room*)malloc(sizeof(t_room));
	new->x = ft_atoi(arr[1]);
	new->y = ft_atoi(arr[2]);
	new->name = ft_strdup(arr[0]);
	new->priority = priority;
	new->next = NULL;
	new->links = NULL;
	new->links_size = 0;
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
	new = (t_room*)malloc(sizeof(t_room));
	new->x = ft_atoi(arr[1]);
	new->y = ft_atoi(arr[2]);
	new->name = ft_strdup(arr[0]);
	new->priority = priority;
	new->next = NULL;
	new->links = NULL;
	new->links_size = 0;
	if (!tmp)
		*room = new;
	else
		tmp->next = new;
}

char	add_room(t_room **room, char *str, char priority)
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
			return (ERROR_NOT_UNIQUE_ROOM);
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
	return (0);
}

char	add_room_with_command(t_room **room, t_list **list, char *flag)
{
	if (ft_strequ((*list)->content, "##start"))
	{
		if ((*flag & 1) == 1)
			return (ERROR_S_START);
		*flag = *flag | 1;
		if (!(*list = (*list)->next) || !is_room((*list)->content))
			return (ERROR_WITH_ROOM);
		else
			return (add_room(room, (*list)->content, START));
	}
	else
	{
		if ((*flag & 2) == 2)
			return (ERROR_S_END);
		*flag = *flag | 2;
		if (!(*list = (*list)->next) || !is_room((*list)->content))
			return (ERROR_WITH_ROOM);
		else
			return (add_room(room, (*list)->content, END));
	}
	return (ERROR_HZ);
}

char	get_rooms(t_str *s, t_list **list)
{
	char	error;
	char	flag;

	flag = 0;
	while (*list)
	{
		if (is_room((*list)->content))
		{
			if ((error = add_room(&s->room, (*list)->content, 0)) != 0)
				return (error);
		}
		else if (is_command((*list)->content))
		{
			if ((error = add_room_with_command(&s->room, list, &flag)) != 0)
				return (error);
		}
		else if (is_link((*list)->content))
			return ((flag == 3) ? 0 : ERROR_NOT_ENOUGH_INFO);
		else if (((char*)(*list)->content)[0] != '#')
			return (ERROR_INVALID_FILE);
		*list = (*list)->next;
	}
	return (ERROR_INVALID_FILE);
}

t_room		**apply_link(t_room **links, t_room *room, int *size, char *error)
{
	t_room	**new_links;
	int		i;

	i = -1;
	while (++i < *size)
		if (ft_strequ(links[i]->name, room->name))
		{
			*error = ERROR_NOT_UNIQUE_LINK;
			return (links);
		}
	new_links = (t_room **)malloc(sizeof(t_room *) * (*size + 1));
	i = -1;
	while (++i < *size)
		new_links[i] = links[i];
	new_links[i] = room;
	i = -1;
	if (*size > 0)
		free(links);
	*size += 1;
	return (new_links);
}

char		connect_links(t_room *room1, t_room *room2)
{
	char	error;

	if (!room1 || !room2 || ft_strequ(room1->name, room2->name))
		return (ERROR_INVALID_LINK);
	error = 0;
	room1->links = apply_link(room1->links, room2, &room1->links_size, &error);
	room2->links = apply_link(room2->links, room1, &room2->links_size, &error);
	if (error != 0)
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
			return (ERROR_INVALID_FILE);
		*list = (*list)->next;
	}
	return (0);
}

char		parsing(t_str *s)
{
	t_list	*tmp;
	char	error;

	s->ants_counter = 0;
	s->room = NULL;
	s->ant = NULL;
	lines_to_list(s);
	tmp = s->line_list;
	if ((error = get_ants_counter(&s->ants_counter, &tmp)) != 0)
	{
		error_management(error);
		line_list_del(&s->line_list);
		return (0);
	}
	if ((error = get_rooms(s, &tmp)) != 0 || (error = get_links(s, &tmp)) != 0)
	{
		error_management(error);
		line_list_del(&s->line_list);
	
		return (0);
	}
	return (1);
}

#include <stdio.h>

int			main(void)
{
	t_str	*s;

	s = (t_str*)malloc(sizeof(t_str));
	if (!parsing(s))
	{
		free(s);
		return (0);
	}


	int i;
	while (s->room)
	{
		i = 0;
		printf("room name = %s, priority = %d, x = %d, y = %d\n", s->room->name, s->room->priority, s->room->x, s->room->y);
		while (i < s->room->links_size)
		{
			printf("link[%d] name: %s\n", i, s->room->links[i]->name);
			i++;
		}
		s->room = s->room->next;
	}
	return 0;
}