/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srheede <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 13:11:04 by srheede           #+#    #+#             */
/*   Updated: 2018/08/29 17:55:29 by srheede          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem-in.h"

t_room	*roomnew(char *name, int x, int y)
{
	t_room *room;

	room = (t_room *)malloc(sizeof(t_room));
	room->name = ft_strdup(name);
	room->x = x;
	room->y = y;
	room->ant = 0;
	room->count = 0;
	room->distance = 0;
	room->end = 0;
	room->links = NULL;
	room->links_head = NULL;
	room->next = NULL;
	return (room);
}

void	create_room(t_lem *lem, char **arr)
{
	char	*x;
	char	*y;

	x = ft_itoa(ft_atoi(arr[1]));
	y = ft_itoa(ft_atoi(arr[2]));
	if (!ft_strcmp(arr[1], x) || !ft_strcmp(arr[2], y))
	{
		if (!lem->rooms)
		{
			lem->rooms = roomnew(arr[0], ft_atoi(x), ft_atoi(y));
			lem->rooms_head = lem->rooms;
		}
		else
		{
			lem->rooms->next = roomnew(arr[0], ft_atoi(x), ft_atoi(y));
			lem->rooms = lem->rooms->next;
		}
	}
	ft_strdel(&x);
	ft_strdel(&y);
}

void	set_start(t_lem *lem)
{
	char	**arr;

	ft_strdel(&lem->buffer);
	get_next_line(0, &lem->buffer);
	arr = ft_strsplit(lem->buffer, ' ');
	if (ft_arrlen(arr) == 3)
		create_room(lem, arr);
	else
	{
		ft_arrdel(arr);
		delmem(lem, 1);
	}
	lem->start = lem->rooms;
	ft_arrdel(arr);
}

void	set_end(t_lem *lem)
{
	char	**arr;

	ft_strdel(&lem->buffer);
	get_next_line(0, &lem->buffer);
	arr = ft_strsplit(lem->buffer, ' ');
	if (ft_arrlen(arr) == 3)
		create_room(lem, arr);
	else
	{
		ft_arrdel(arr);
		delmem(lem, 1);
	}
	lem->end = lem->rooms;
	ft_arrdel(arr);
}

int		check_start(t_lem *lem)
{
	if (!ft_strcmp(lem->buffer, "##start"))
	{
		ft_putstr("##start\n");
		if (lem->start)
			delmem(lem, 1);
		set_start(lem);
		return (1);
	}
	if (!ft_strcmp(lem->buffer, "##end"))
	{
		ft_putstr("##end\n");
		if (lem->end)
			delmem(lem, 1);
		set_end(lem);
		return (1);
	}
	return (0);
}
