/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srheede <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 13:11:04 by srheede           #+#    #+#             */
/*   Updated: 2018/08/29 17:55:29 by srheede          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem-in.h"

void	set_zero(t_lem *lem)
{
	lem->rooms = NULL;
	lem->head = NULL;
	lem->arr = NULL;
	lem->start = NULL;
	lem->end = NULL;
	lem->buffer = NULL;
	lem->number = NULL;
	lem->n_ants = 0;
	lem->visualizer = 0;
}

void	delmem(t_lem *lem, int err)
{
	if (lem->arr)
		free(lem->arr);
	if (lem->buffer)
		ft_strdel(&lem->buffer);
	if (lem->number)
		ft_strdel(&lem->number);
	if (err)
		ft_putstr("Error\n");
	exit(0);
}

void	count_ants(t_lem *lem)
{
	get_next_line(0, &lem->buffer);
	lem->number = ft_itoa(ft_atoi(lem->buffer));
	if (strcmp(lem->buffer, lem->number))
		delmem(lem, 1);
	lem->n_ants = ft_atoi(lem->buffer);
	ft_strdel(&lem->number);
	ft_strdel(&lem->buffer);
}

t_room	*roomnew(char *name, int x, int y)
{
	t_room *room;

	room = (t_room *)malloc(sizeof(t_room));
	room->name = name;
	room->x = x;
	room->y = y;
	room->count = 0;
	room->distance = 0;
	room->end = 0;
	room->links = NULL;
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
			lem->head = lem->rooms;
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
	lem->rooms->end = 1;
	ft_arrdel(arr);
}

int		check_start(t_lem *lem)
{
	if (!ft_strcmp(lem->buffer, "##start"))
	{
		if (lem->start)
			delmem(lem, 1);
		set_start(lem);
		return (1);
	}
	if (!ft_strcmp(lem->buffer, "##end"))
	{
		if (lem->end)
			delmem(lem, 1);
		set_end(lem);
		return (1);
	}
	return (0);
}

t_links	*linknew(t_room *room)
{
	t_links *links;

	links = (t_links *)malloc(sizeof(t_links));
	links->room = room;
	links->next = NULL;
	return (links);
}

void	create_link(t_room *first, t_room *second)
{
	if (!first->links)
	{
		first->links = linknew(second);
		first->head = first->links;
	}
	else
	{
		first->links->next = linknew(second);
		first->links = first->links->next;
	}
}

void	link_rooms(t_room *first, t_room *second)
{
	create_link(first, second);
	create_link(second, first);
}

void	assign_link(t_lem *lem)
{
	char	**arr;
	t_room	*tmp;
	t_room	*first;

	ft_putstr("hello");
	arr = ft_strsplit(lem->buffer, '-');
	if (ft_arrlen(arr) != 2)
	{
		tmp = lem->head;
		while (tmp->next)
		{
			if (!ft_strcmp(tmp->name, arr[0]))
			{
				first = tmp;
				break ;
			}
			tmp = tmp->next;
		}
		tmp = lem->head;
		while (tmp->next)
		{
			if (!ft_strcmp(tmp->name, arr[1]))
				break ;
			tmp = tmp->next;
		}
		if (tmp && first)
			link_rooms(tmp, first);
	}
	ft_arrdel(arr);
	ft_putstr("hello");
}

void	read_input(t_lem *lem)
{
	char	**arr;

	while (get_next_line(0, &lem->buffer))
	{
		if (!check_start(lem) && lem->buffer[0] != '#')
		{
			arr = ft_strsplit(lem->buffer, ' ');
			if (ft_arrlen(arr) == 3 && lem->buffer[0] != 'L')
				create_room(lem, arr);
			else if (ft_arrlen(arr) == 1)
				assign_link(lem);
			ft_arrdel(arr);
		}
		else if (lem->buffer[0] == '#')
			ft_putstr(lem->buffer);
		ft_strdel(&lem->buffer);
	}
	if (lem->buffer)
		ft_strdel(&lem->buffer);
}

int		main(int argc, char **argv)
{
	t_lem	lem;

	set_zero(&lem);
	if (argc == 2)
		if (strcmp(argv[1], "-v"))
			lem.visualizer = 1;
	count_ants(&lem);
	read_input(&lem);
	delmem(&lem, 0);
	return (0);
}
