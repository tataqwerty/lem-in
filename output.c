/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 10:29:18 by tkiselev          #+#    #+#             */
/*   Updated: 2018/05/08 19:48:22 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				error(char error)
{
	ft_putstr("Error: ");
	error == ERROR_INVALID_FILE ? ft_putstr("invalid file.\n") : 0;
	error == ERROR_INVALID_QUANTITY_OF_ANTS ?
		ft_putstr("invalid quantity of ants.\n") : 0;
	error == ERROR_WITH_ROOM ? ft_putstr("not a valid room.\n") : 0;
	error == ERROR_NOT_UNIQUE_ROOM ? ft_putstr("not unique room.\n") : 0;
	error == ERROR_SECOND_START ? ft_putstr("several starts.\n") : 0;
	error == ERROR_SECOND_END ? ft_putstr("several ends.\n") : 0;
	error == ERROR_NOT_ENOUGH_INFO ?
		ft_putstr("not enough information.\n") : 0;
	error == ERROR_INVALID_LINK ? ft_putstr("invalid link.\n") : 0;
	error == ERROR_INVALID_ORDER ? ft_putstr("invalid order.\n") : 0;
	error == ERROR_NO_ANTS ? ft_putstr("no ants.\n") : 0;
	error == ERROR_WITH_START_ROOM ?
		ft_putstr("with room after ##start.\n") : 0;
	error == ERROR_WITH_END_ROOM ? ft_putstr("with room after ##end.\n") : 0;
	error == ERROR_NO_SOLUTION ? ft_putstr("no solution.\n") : 0;
	exit(0);
}

void				send_ants(t_ways **ways, int ways_size,int *ants_counter,
					char *flag)
{
	t_way			*way;
	int				i;

	i = -1;
	while (++i < ways_size)
	{
		way = ways[i]->way;
		while (way->next && way->next->room->priority != START)
			way = way->next;
		if (ways[i]->length <= (ways[0]->length + way->next->room->ants - 1)
			&& way->next->room->ants > 0)
		{
			if (*flag)
				ft_printf(" ");
			*flag = 1;
			ft_printf("L%d-%s", ++(*ants_counter), way->room->name);
			way->room->ant_id = *ants_counter;
			way->room->ants++;
			way->next->room->ants--;
		}
	}
}

void				bring_remaining_ants(t_ways **ways, int ways_size,
					char *flag)
{
	t_way			*way;
	int				i;

	i = -1;
	while (++i < ways_size)
	{
		way = ways[i]->way;
		while (way->next && way->next->room->priority != START)
		{
			if (way->next->room->ants > 0)
			{
				if (*flag)
					ft_printf(" ");
				*flag = 1;
				ft_printf("L%d-%s", way->next->room->ant_id, way->room->name);
				way->room->ant_id = way->next->room->ant_id;
				way->next->room->ant_id = 0;
				way->room->ants++;
				way->next->room->ants--;
			}
			way = way->next;
		}
	}
}

void				print_steps(t_str *s, t_room *end)
{
	int				ants_counter;
	char			flag;

	flag = 0;
	ants_counter = 0;
	if (s->ways[0]->length == 1)
	{
		while (end->ants < s->ants_counter)
		{
			if (flag)
				ft_printf(" ");
			ft_printf("L%d-%s", ++end->ants, s->ways[0]->way->room->name);
			flag = 1;
			s->room->ants--;
		}
		ft_printf("\n");
		return ;
	}
	while (end->ants < s->ants_counter)
	{
		flag = 0;
		bring_remaining_ants(s->ways, s->ways_size, &flag);
		send_ants(s->ways, s->ways_size, &ants_counter, &flag);
		ft_printf("\n");
	}
}

void				output(t_str *s)
{
	t_room			*end;
	t_list			*tmp_list;

	tmp_list = s->line_list;
	while (tmp_list)
	{
		ft_putendl(tmp_list->content);
		tmp_list = tmp_list->next;
	}
	ft_printf("\n");
	s->room->ants = s->ants_counter;
	end = s->room;
	while (end && end->priority != END)
		end = end->next;
	print_steps(s, end);
}
