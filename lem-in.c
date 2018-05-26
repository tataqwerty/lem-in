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

void		ft_list_pushback(t_list **head, char *line)
{
	t_list	*tmp;
	t_list	*new;

	tmp = *head;
	while (tmp)
	{
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	if (!(new = (t_list*)malloc(sizeof(t_list))))
		return ;
	new->content = ft_strdup(line);
	new->content_size = 0;
	new->next = NULL;
	if (!*head)
		*head = new;
	else
		tmp->next = new;
}

void		get_all_lines(t_list **head, int *lines)
{
	char	*line;

	line = NULL;
	while (get_next_line(0, &line) > 0)
	{
		ft_list_pushback(head, line);
		free(line);
		*lines++;
	}
}

char		get_rooms_counter(t_str *s, t_list **list)
{
	if (!*list || !(*list)->content)
	{
		ft_putstr("Empty file\n");
		return (0);
	}
	s->rooms = ft_atoi((*list)->content);
	if (s->rooms == 0)
	{
		ft_putstr("Quantity of rooms equal to zero!\n");
		return (0);
	}
	*list = (*list)->next;
	return (1);
}

char		is_room(char *str)
{
	char tmp;
	int i;

	tmp = 0;
	i = 0;
	if (!str || str[0] == '\0' || str[0] == 'L' || str[0] == '#')
		return (0);
	while (str[i] > 32 && str[i] < 127 && i++)
		tmp = 1;
	if (tmp == 0 || str[i++] != ' ')
		return (0);
	tmp = 0;
	while (str[i] >= '0' && str[i] <= '9' && i++)
		tmp = 1;
	if (tmp == 0 || str[i++] != ' ')
		return (0);
	tmp = 0;
	while (str[i] >= '0' && str[i] <= '9' && i++)
		tmp = 1;
	if (tmp == 0 || str[i++] != '\0')
		return (0);
	return (1);
}

char		is_link(char *str)
{
	char	tmp;
	int		i;

	tmp = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0' && str[i] != '-'
		&& str[i] > 32 && str[i] < 127 && i++)
		tmp = 1;
	if (tmp == 0 || str[i++] != '-')
		return (0);
	tmp = 0;
	while (str[i] != '\0' && str[i] != '-'
		&& str[i] > 32 && str[i] < 127 && i++)
		tmp = 1;
	if (tmp == 0 || str[i] != '\0')
		return (0);
	return (1);
}

char		add_room(t_str *s, char *line, char priority)
{

}

char		get_rooms(t_main *s, t_list **list)
{
	while (*list)
	{
		if (ft_strcmp((*list)->content, "##start") || ft_strcmp((*list)->content, "##end"))
		{
			*list = (*list)->next;
			if (is_room((*list)->content))
			{
				if (!add_room())
					return (0);
			}
			else
			{
				ft_putstr("Error");
				return (0);
			}
		}
		*list = (*list)->next;
	}
	return (1);
}

char		parsing(t_str *s)
{
	t_list *list;

	s->line_list = NULL;
	s->lines = 0;
	get_all_lines(&s->line_list, &s->lines);
	list = s->line_list;
	if (!get_rooms_counter(s, &list) || !get_rooms(s, &list) ||
	!get_links(s, &list)) // Сдвигаю list и его не нужно фришить
	{
		listdel(s->line_list);
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
		return (0);
	return (0);
}