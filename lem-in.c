#include <stdio.h>
#include "libft.h"
#include "lem-in.h"

void		listdel(t_list **head)
{
	t_list	*tmp;

	if (!head || !*head)
		return ;
	while (*head)
	{
		tmp = (*head)->next;
		free((*head)->content);
		free(*head);
		*head = tmp;
	}
	*head = NULL;
}

void		roomsdel(t_room *room)
{

}

//////////////////
void		ft_puterror(char *str)
{
	ft_putstr("Error: ");
	ft_putstr(str);
}

void		error_management(char error)
{
	if (error == INV_FILE)
		ft_puterror("Invalid file.\n");
	else if (error == INV_ANTS)
		ft_puterror("Invalid quantity of ants.\n");
	else if (error == LINK_BEFORE_ROOM)
		ft_puterror("No room yet.\n");
	else if (error == WTF)
		ft_puterror("wtf?.\n");
	
}
//////// Вместо этой хуйни макрос зафигачить.

void		get_all_lines(t_list **head)
{
	char	*line;

	line = NULL;
	while (get_next_line(0, &line) > 0)
	{
		ft_list_pushback(head, line);
		free(line);
	}
}

char		get_counter_ants(t_list **list)
{
	int		i;

	i = 0;
	if (!list || !*list || (*list)->content_size == 0)
		return (INV_FILE); // Invalid file.
	while (((char*)(*list)->content)[i] >= '0' && ((char*)(*list)->content)[i] <= '9')
		s->rooms_counter = s->rooms_counter * 10 + ((char*)(*list)->content)[i++] - 48;
	if (s->rooms_counter == 0 || ((char*)(*list)->content)[i] != '\0')
		return (INV_ANTS); // Invalid quantity of ants.
	*list = (*list)->next;
	return (0);
}

char		is_command(char *str)
{
	if (ft_strcmp(str, "##start") == 0 || ft_strcmp(str, "##end") == 0)
		return (1);
	return (0);
}

char		is_room(char *str)
{
	char	flag;
	int		i;

	i = 0;
	if (!str || str[0] == 'L' || str[i] == '#')
		return (0);
	flag = 0;
	while (str[i] != '-' && str[i] > 32 && str[i] < 127 && i++)
		flag = 1;
	if (flag == 0 || str[i++] != ' ')
		return (0);
	flag = 0;
	while (str[i] >= '0' && str[i] <= '9' && i++)
		flag = 1;
	if (flag == 0 || str[i++] != ' ')
		return (0);
	flag = 0;
	while (str[i] >= '0' && str[i] <= '9' && i++)
		flag = 1;
	if (flag == 0 || str[i] != '\0')
		return (0);
	return (1);
}

char		is_link(char *str)
{
	int		i;
	char	flag;

	flag = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i] != '-' && str[i] > 32 && str[i] < 127 && i++)
		flag = 1;
	if (flag == 0 || str[i++] != '-')
		return (0);
	while (str[i] != '-' && str[i] > 32 && str[i] < 127 && i++)
		flag = 1;
	if (flag == 0 || str[i] != '\0')
		return (0);
	return (1);
}

char		add_room(char *str, int priority)
{
	
}

char		ft_for_command(t_list **list, char *flag)
{
	char	error;

	if (ft_strcmp((*list)->content, "##start") == 0)
	{
		if ((*flag) & 1 == 1)
			return (SEVERAL_STARTS);
		*flag = (*flag) | 1;
		if (!(*list = (*list)->next) || !is_room((*list)->content))
			return (NOT_A_ROOM);
		else if ((error = add_room((*list)->content, 1)) != 0)
			return (error);
	}
	else if (ft_strcmp((*list)->content, "##end") == 0)
	{
		if ((*flag) & 2 == 2)
			return (SEVERAL_ENDS);
		*flag = (*flag) | 2;
		if (!(*list = (*list)->next) || !is_room((*list)->content))
			return (NOT_A_ROOM);
		else if ((error = add_room((*list)->content, 2)) != 0)
			return (error);
	}
	return (0);
}

char		get_rooms(t_str *s, t_list **list)
{
	char	flag;
	char	error;

	flag = 0;
	while (*list)
	{
		if (is_command((*list)->content))
			if ((error = ft_for_command(list, &flag)) != 0)
				return (error);
		else if (is_room((*list)->content))
			if ((error = add_room((*list)->content, 0)) != 0)
				return (error);
		else if (is_link((*list)->content))
			if (flag & 4 == 0) // линк перед комнатой.
				return (LINK_BEFORE_ROOM);
			else
				return (0);
		else if ((*list)->content[0] != '#')
			return (WTF); // ХЗ что за херня.
		*list = (*list)->next;
	}
	return (0);
}

char		get_links(t_str *s, t_list **list)
{
	// накостылить, чтоб брался первый линк.

}

char		parsing(t_str *s)
{
	char	error;
	t_list	*list;

	s->line_list = NULL;
	s->rooms_counter = 0;
	s->room = NULL;
	get_all_lines(&s->line_list);
	list = s->line_list;
	if ((error = get_counter_ants(&list)) != 0)
	{
		error_management(error);
		listdel(&s->line_list);
		return (0);
	}
	if ((error = get_rooms(s, &list)) != 0 || (error = get_links(s, &list)) != 0)
	{
		error_management(error);
		listdel(&s->line_list);
		if (s->room)
			delrooms(&s->room);
		return (0);
	}
	return (1);
}

int			main(void)
{
	t_str	*s;

	if (!(s = (t_str*)malloc(sizeof(t_str))))
		return (0);
	if (!parsing(s))
	{
		free(s);
		return (0);
	}
	return (0);
}