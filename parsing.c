/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 10:29:18 by tkiselev          #+#    #+#             */
/*   Updated: 2018/05/08 19:48:22 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				get_ants_counter(unsigned int *counter, t_list **list)
{
	int				i;
	char			*line;

	line = NULL;
	while (get_next_line(0, &line) > 0)
	{
		ft_list_pushback(list, line);
		if (is_comment(line))
			continue ;
		else if (line[0] >= '0' && line[0] <= '9')
			break ;
		else
			error(ERROR_INVALID_QUANTITY_OF_ANTS);
		ft_strdel(&line);
	}
	(!line) ? error(ERROR_INVALID_QUANTITY_OF_ANTS) : 0;
	i = 0;
	while (line[i] && line[i] >= '0' && line[i] <= '9')
	{
		if ((*counter == 429496729 && line[i] >= '6') || *counter > 429496729)
			error(ERROR_INVALID_QUANTITY_OF_ANTS);
		*counter = *counter * 10 + line[i++] - '0';
	}
	(line[i] != '\0') ? error(ERROR_INVALID_QUANTITY_OF_ANTS) : 0;
	ft_strdel(&line);
}

char				get_links(t_str *s, char *line)
{
	while (line)
	{
		if (is_link(line))
		{
			if (!find_place_n_connect_links(&s->room, line))
			{
				ft_strdel(&line);
				return (ERROR_INVALID_LINK);
			}
		}
		else if (!is_comment(line))
		{
			ft_strdel(&line);
			return (ERROR_INVALID_ORDER);
		}
		ft_list_pushback(&s->line_list, line);
		ft_strdel(&line);
		get_next_line(0, &line);
	}
	return (0);
}

char				get_rooms_and_links(t_str *s)
{
	char			flag;
	char			*line;

	flag = 0;
	line = NULL;
	while (get_next_line(0, &line) > 0)
	{
		if (is_room(line))
			add_room(&s->room, line, 0);
		else if (is_command(line))
			add_room_with_command(s, &line, &flag);
		else if (is_link(line))
		{
			(flag != 3) ? error(ERROR_NOT_ENOUGH_INFO) : 0;
			return (get_links(s, line));
		}
		else if (line[0] != '#')
			error(ERROR_INVALID_FILE);
		ft_list_pushback(&s->line_list, line);
		ft_strdel(&line);
	}
	error(ERROR_NOT_ENOUGH_INFO);
	return (0);
}

char				parsing(t_str *s)
{
	char			err;

	s->ants_counter = 0;
	s->room = NULL;
	s->line_list = NULL;
	get_ants_counter(&s->ants_counter, &s->line_list);
	err = get_rooms_and_links(s);
	return (err);
}
