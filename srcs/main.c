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
	lem->rooms_head = NULL;
	lem->arr = NULL;
	lem->start = NULL;
	lem->end = NULL;
	lem->buffer = NULL;
	lem->number = NULL;
	lem->n_ants = 0;
	lem->count = 0;
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

void	read_input(t_lem *lem)
{
	char	**arr;

	while (get_next_line(0, &lem->buffer))
	{
		if(!check_start(lem) && lem->buffer[0] != '#')
		{
			arr = ft_strsplit(lem->buffer, ' ');
			if (ft_arrlen(arr) == 3 && lem->buffer[0] != 'L')
				create_room(lem, arr);
			else if (ft_arrlen(arr) == 1)
				assign_links(lem);
			ft_arrdel(arr);
		}
		else if (lem->buffer[0] == '#')
		{
			ft_putstr(lem->buffer);
			ft_putchar('\n');
		}
		ft_strdel(&lem->buffer);
	}
	if (lem->buffer)
		ft_strdel(&lem->buffer);
}

void	assign_values(t_lem *lem, t_room *tmp)
{
	t_links *tmp_links;
	t_room	*room;

	lem->count++;
	tmp_links = tmp->links_head;
	while (tmp_links)
	{
		room = (t_room *)tmp_links->room;
		if ((room->end > lem->count || room->end == 0) && room != lem->end)
		{
			room->end = lem->count;
			assign_values(lem, room);
		}
		tmp_links = tmp_links->next;
	}
	lem->count--;
}

int		main(int argc, char **argv)
{
	t_lem	lem;
	t_room	*tmp;

	set_zero(&lem);
	if (argc == 2)
		if (strcmp(argv[1], "-v"))
			lem.visualizer = 1;
	count_ants(&lem);
	ft_putstr("ant count: ");
	ft_putnbr(lem.n_ants);
	ft_putchar('\n');
	read_input(&lem);
	assign_values(&lem, lem.end);
	while (lem.rooms_head)
	{
		ft_putstr("\nroom name: ");
		ft_putstr(lem.rooms_head->name);
		ft_putchar('\n');
		ft_putstr("room x coordinate: ");
		ft_putnbr(lem.rooms_head->x);
		ft_putchar('\n');
		ft_putstr("room y coordinate: ");
		ft_putnbr(lem.rooms_head->y);
		ft_putchar('\n');
		while (lem.rooms_head->links_head)
		{
			ft_putstr("link in room ");
			ft_putstr(lem.rooms_head->name);
			ft_putstr(": ");
			tmp = (t_room *)lem.rooms_head->links_head->room;
			ft_putstr(tmp->name);
			ft_putchar('\n');
			ft_putstr("link value: ");
			ft_putnbr(tmp->end);
			ft_putchar('\n');
			lem.rooms_head->links_head = lem.rooms_head->links_head->next;
		}
		lem.rooms_head = lem.rooms_head->next;
	}
			ft_putstr("start name: ");
		if (lem.start)
			ft_putstr(lem.start->name);
		ft_putchar('\n');
				ft_putstr("end name: ");
		if (lem.end)
			ft_putstr(lem.end->name);
		ft_putchar('\n');
	delmem(&lem, 0);
	return (0);
}
