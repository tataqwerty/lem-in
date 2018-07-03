/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 10:29:18 by tkiselev          #+#    #+#             */
/*   Updated: 2018/05/08 19:48:22 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	is_command(char *str)
{
	if (ft_strequ(str, "##start") || ft_strequ(str, "##end"))
		return (1);
	return (0);
}

char	is_room(char *str)
{
	char	flag;
	int		i;

	if (!str || str[0] == 'L' || str[0] == '#')
		return (0);
	flag = 0;
	i = 0;
	while (str[i] != '\0' && str[i] > 32 && str[i] < 127
		&& str[i] != '-' && (flag = 1))
		i++;
	if (flag != 1 || str[i++] != ' ')
		return (0);
	(str[i] == '-' || str[i] == '+') ? i++ : 0;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9' && (flag = 2))
		i++;
	if (flag != 2 || str[i++] != ' ')
		return (0);
	(str[i] == '-' || str[i] == '+') ? i++ : 0;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9' && (flag = 3))
		i++;
	if (flag != 3 || str[i] != '\0')
		return (0);
	return (1);
}

char	is_link(char *s)
{
	int		i;
	char	flag;

	if (!s || s[0] == 'L' || s[0] == '#')
		return (0);
	i = 0;
	flag = 0;
	while (s[i] > 32 && s[i] < 127 && s[i] != '-' && (flag = 1))
		i++;
	if (flag != 1 || s[i++] != '-' || s[i] == 'L' || s[i] == '#')
		return (0);
	while (s[i] > 32 && s[i] < 127 && s[i] != '-' && (flag = 2))
		i++;
	if (flag != 2 || s[i] != '\0')
		return (0);
	return (1);
}

char	is_comment(char *str)
{
	if (is_command(str))
		return (0);
	else if (str[0] == '#')
		return (1);
	return (0);
}

char	is_int(char *str)
{
	int		res;
	int		i;

	res = 0;
	i = 0;
	if (ft_strequ(str, "-2147483648"))
		return (1);
	(str[0] == '-' || str[0] == '+') ? i++ : 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((res == 214748364 && str[i] >= '8') || res > 214748365)
			return (0);
		res = res * 10 + str[i++] - '0';
	}
	return (1);
}
