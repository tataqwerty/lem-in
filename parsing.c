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

void		get_rooms(t_str *s, t_list **list)
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
			if ((error = find_place_n_connect_links(&s->room,
				(*list)->content)) != 0)
				return (error);
		}
		else if (((char*)(*list)->content)[0] != '#')
			return (ERROR_INVALID_ORDER);
		*list = (*list)->next;
	}
	return (0);
}

char		parsing(t_str *s)
{
	t_list	*tmp;
	char	err;

	s->ants_counter = 0;
	s->room = NULL;
	lines_to_list(s);
	tmp = s->line_list;
	if (!tmp)
		error(ERROR_INVALID_FILE);
	get_ants_counter(&s->ants_counter, &tmp);
	get_rooms(s, &tmp);
	err = get_links(s, &tmp);
	if (err != 0)
		find_and_delete_list(s->line_list, tmp);
	return (err);
}
