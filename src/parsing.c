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

void				get_ants_counter(int *counter, t_list **list, char *line)
{
	while (get_next_line(0, &line) > 0 && is_comment(line))
	{
		ft_list_pushback(list, line);
		ft_strdel(&line);
	}
	(!line) ? error(ERROR_INVALID_FILE) : 0;
	(!is_int(line)) ? error(ERROR_INVALID_QUANTITY_OF_ANTS) : 0;
	*counter = ft_atoi(line);
	(*counter <= 0) ? error(ERROR_INVALID_QUANTITY_OF_ANTS) : 0;
	ft_list_pushback(list, line);
	ft_strdel(&line);
}

char				get_links(t_str *s, char **line)
{
	while (*line)
	{
		if (is_link(*line))
		{
			if (!find_place_n_connect_links(&s->room, *line))
			{
				ft_strdel(line);
				return (ERROR_INVALID_LINK);
			}
		}
		else if (!is_comment(*line))
		{
			ft_strdel(line);
			return (0);
		}
		ft_list_pushback(&s->line_list, *line);
		ft_strdel(line);
		get_next_line(0, line);
	}
	return (0);
}

void				get_rooms(t_str *s, char **line)
{
	char			flag;

	flag = 0;
	while (get_next_line(0, line) > 0)
	{
		if (is_room(*line))
			add_room(&s->room, *line, 0);
		else if (is_command(*line))
			add_room_with_command(s, line, &flag);
		else if (is_link(*line))
		{
			if (flag != 3)
				break ;
			else
				return ;
		}
		else if (!is_comment(*line))
			error(ERROR_INVALID_FILE);
		ft_list_pushback(&s->line_list, *line);
		ft_strdel(line);
	}
	error(ERROR_NOT_ENOUGH_INFO);
}

char				parsing(t_str *s)
{
	char			*line;

	line = NULL;
	s->ants_counter = 0;
	s->room = NULL;
	s->line_list = NULL;
	get_ants_counter(&s->ants_counter, &s->line_list, line);
	get_rooms(s, &line);
	return (get_links(s, &line));
}
