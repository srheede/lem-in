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
		if (room == lem->start)
			break ;
		if ((room->end > lem->count || room->end == 0) && room != lem->end)
		{
			room->end = lem->count;
			assign_values(lem, room);
		}
		tmp_links = tmp_links->next;
	}
	lem->count--;
}

t_room	*choose_room(t_room *current)
{
	t_links *links;
	t_room	*room;
	t_room	*tmp;

	links = current->links_head;
	tmp = NULL;
	while (links)
	{
		room = (t_room *)links->room;
		if (!room->ant)
		{
			if ((!tmp || tmp->end > room->end) && room->end)
				tmp = room;
		}
		links = links->next;
	}
	return(tmp);
}

void	send_ants(t_lem *lem)
{
	t_room	*room;
	t_room	*tmp;
	t_links	*pos_ants;
	int		count;

	count = 1;
	room = choose_room(lem->start);
	pos_ants = linknew(room);
	lem->pos_ants = pos_ants;
	while(room)
	{
		room->ant = count;
		count++;
		lem->n_ants--;
		room = choose_room(lem->start);
		pos_ants->next = linknew(room);
		pos_ants = pos_ants->next;
	}
	pos_ants = lem->pos_ants;
	while (pos_ants->next)
	{
		tmp = (t_room *)pos_ants->room;
		room = choose_room(tmp);
		room->ant = tmp->ant;
		tmp->ant = 0;
		pos_ants = pos_ants->next;
	}
	while (lem->rooms_head)
	{
		ft_putstr(lem->rooms_head->name);
		ft_putchar(' ');
		ft_putnbr(lem->rooms_head->ant);
		ft_putchar(' ');
		lem->rooms_head = lem->rooms_head->next;
	}
}
/*
void	move_ants(t_lem *lem)
{

}
*/
int		main(int argc, char **argv)
{
	t_lem	lem;

	set_zero(&lem);
	if (argc == 2)
		if (strcmp(argv[1], "-v"))
			lem.visualizer = 1;
	count_ants(&lem);
	read_input(&lem);
	assign_values(&lem, lem.end);
	send_ants(&lem);
	delmem(&lem, 0);
	return (0);
}
