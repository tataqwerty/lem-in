/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 10:29:18 by tkiselev          #+#    #+#             */
/*   Updated: 2018/05/08 19:48:22 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
