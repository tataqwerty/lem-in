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

void		apply_link(t_room ***links, t_room *room, int *size)
{
	t_room	**new_arr;
	int		i;

	i = -1;
	while (++i < *size)
	{
		if (ft_strequ((*links)[i]->name, room->name))
			return ;
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
	while (tmp1 && ft_strequ(tmp1->name, arr[0]) == 0)
		tmp1 = tmp1->next;
	while (tmp2 && ft_strequ(tmp2->name, arr[1]) == 0)
		tmp2 = tmp2->next;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	if (!tmp1 || !tmp2 || ft_strequ(tmp1->name, tmp2->name))
		return (0);
	apply_link(&tmp1->links, tmp2, &tmp1->links_size);
	apply_link(&tmp2->links, tmp1, &tmp2->links_size);
	return (1);
}
