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

void				send_ants(t_ways **ways, int ways_size, int *ants_counter,
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
			(*flag) ? ft_printf(" ") : 0;
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
				(*flag) ? ft_printf(" ") : 0;
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
			(flag) ? ft_printf(" ") : 0;
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
