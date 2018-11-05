/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 10:29:18 by tkiselev          #+#    #+#             */
/*   Updated: 2018/05/08 19:48:22 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			main(void)
{
	t_str	*s;
	char	err;

	s = (t_str*)malloc(sizeof(t_str));
	err = parsing(s);
	generate_ways(s);
	if (!s->ways)
		error((err == 0) ? ERROR_NO_SOLUTION : err);
	output(s);
	system("leaks lem-in");
	return (0);
}
