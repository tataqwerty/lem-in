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

char		is_command(char *str)
{
	if (!str)
		return (0);
	if (ft_strequ(str, "##start") || ft_strequ(str, "##end"))
		return (1);
	return (0);
}

char		is_room(char *str)
{
	char	**arr;
	int		i;
	char	flag;

	if (!str || !(arr = ft_strsplit(str, ' ')))
		return (0);
	i = 0;
	flag = 1;
	while (arr[i])
	{
		if (i == 0 && (arr[i][0] == 'L' || arr[i][0] == '#'
			|| ft_strchr(arr[i], '-')))
			flag = 0;
		else if ((i == 1 || i == 2) && !is_int(arr[i]))
			flag = 0;
		free(arr[i++]);
	}
	free(arr);
	(i != 3) ? (flag = 0) : 0;
	return (flag);
}

char		is_link(char *s)
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

char		is_comment(char *str)
{
	if (!str || is_command(str))
		return (0);
	else if (str[0] == '#')
		return (1);
	return (0);
}

char		is_int(char *str)
{
	int		res;
	int		i;

	if (!str)
		return (0);
	res = 0;
	i = 0;
	if (ft_strequ(str, "-2147483648"))
		return (1);
	(str[0] == '-' || str[0] == '+') ? str++ : 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((res == 214748364 && str[i] >= '8') || res > 214748365)
			return (0);
		res = res * 10 + str[i++] - '0';
	}
	return ((i > 0 && str[i] == '\0') ? 1 : 0);
}
