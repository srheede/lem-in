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
	lem->n_end = 0;
	lem->count = 0;
	lem->visualizer = 0;
	lem->pos_ants = NULL;
	lem->pos_new = NULL;
	lem->pos_new_last = NULL;
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
	ft_putchar('\n');
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

t_room	*choose_room(t_lem *lem, t_room *current)
{
	t_links *links;
	t_room	*room;
	t_room	*tmp;

	links = current->links_head;
	tmp = NULL;
	if (current == lem->end)
		return(tmp);
	while (links)
	{
		room = (t_room *)links->room;
		if (room == lem->end)
		{
			tmp = room;
			lem->n_end--;
			break ;
		}
		if (!room->ant)
		{
			if ((!tmp || tmp->end > room->end) && room->end)
				tmp = room;
		}
		links = links->next;
	}
	return(tmp);
}

int		move_ants(t_lem *lem)
{
	t_room	*room;
	t_room	*tmp;
	t_links *pos_ants;
	t_links	*pos_new;
	t_links	*tmp_node;

	pos_new = NULL;
	pos_ants = lem->pos_ants;
	tmp = (t_room *)pos_ants->room;
	room = choose_room(lem, tmp);
	if (!room && pos_ants->next)
	{
		pos_new = linknew(tmp);
		lem->pos_new = pos_new;
		lem->pos_ants = pos_new;
		pos_ants = pos_ants->next;
		tmp = (t_room *)pos_ants->room;
		room = choose_room(lem, tmp);
	}
	else if (!room)
		return (0);
	while (room == lem->end && pos_ants->next)
	{
		room->ant = tmp->ant;
		tmp->ant = 0;
		tmp_node = pos_ants;
		pos_ants = pos_ants->next;
		if (pos_ants)
		{
			tmp = (t_room *)pos_ants->room;
			room = choose_room(lem, tmp);
			if (!room && !pos_new)
			{
				pos_new = linknew(tmp);
				lem->pos_new = pos_new;
				lem->pos_ants = pos_new;	
				pos_ants = pos_ants->next;
				if (pos_ants)
				{
					tmp = (t_room *)pos_ants->room;
					room = choose_room(lem, tmp);
				}
			}
			else if (!room && pos_new)
			{
				pos_new->next = linknew(room);
				pos_new = pos_new->next;
				lem->pos_new_last = pos_new;
				if (pos_ants)
				{
					tmp = (t_room *)pos_ants->room;
					room = choose_room(lem, tmp);
				}
			}
			else if (room != lem->end && pos_new)
			{
				pos_new->next = linknew(room);
				pos_new = pos_new->next;
				lem->pos_new_last = pos_new;
			}
			else if (room != lem->end)
			{
				pos_new = linknew(room);
				lem->pos_new = pos_new;
				lem->pos_ants = pos_new;
			}
		}		
	}
	if (!pos_new)
	{
		pos_new = linknew(room);
		lem->pos_new = pos_new;
		lem->pos_ants = pos_new;
	}
	while (pos_ants)
	{
		room->ant = tmp->ant;
		tmp->ant = 0;
		tmp_node = pos_ants;
		pos_ants = pos_ants->next;
		if (pos_ants)
		{
			tmp = (t_room *)pos_ants->room;
			room = choose_room(lem, tmp);
			if (!room)
			{
				pos_new->next = linknew(tmp);
				pos_new = pos_new->next;
				lem->pos_new_last = pos_new;			
				free(tmp_node);
				break ;
			}
			if (room != lem->end)
			{
				pos_new->next = linknew(room);
				pos_new = pos_new->next;
				lem->pos_new_last = pos_new;
			}
		}
		free(tmp_node);
	}
	return (0);
}

void	search_party(t_lem *lem)
{
	t_room	*room;

	lem->pos_ants = NULL;
	room = lem->rooms_head;
	while (room)
	{
		if (room != lem->end)
		{
			if (room->ant && !lem->pos_ants)
			{
				lem->pos_new = linknew(room);
				lem->pos_ants = lem->pos_new;
			}
			else if (room->ant)
			{
				lem->pos_new->next = linknew(room);
				lem->pos_new = lem->pos_new->next;
			}
		}
		room = room->next;
	}
}

void	visualize(t_lem *lem)
{
	t_room	*room;

	if (lem->visualizer)
	{
		room = lem->rooms_head;
		while (room)
		{
			ft_putstr("\n");
			ft_putstr(room->name);
			ft_putchar(' ');
			ft_putnbr(room->ant);
			ft_putchar(' ');
			room = room->next;
		}
		ft_putstr("\n");
		sleep(1);
	}
}

void	send_ants(t_lem *lem)
{
	t_room	*room;
	t_links	*pos_ants;
	int		count;

	count = 1;
	while (lem->n_ants)
	{
		room = choose_room(lem, lem->start);
		pos_ants = linknew(room);
		lem->pos_ants = pos_ants;
		while(room)
		{
			room->ant = count;
			count++;
			lem->n_ants--;
			if (!lem->n_ants)
				break ;
			room = choose_room(lem, lem->start);
			if (!room)
				break ;
			pos_ants->next = linknew(room);
			pos_ants = pos_ants->next;
		}
		if (lem->pos_new)
		{
			pos_ants = lem->pos_ants;
			lem->pos_ants = lem->pos_new;
			lem->pos_new_last->next = pos_ants;
		}
		visualize(lem);
		move_ants(lem);
	}
	while (lem->end->ant != lem->n_total)
	{
		visualize(lem);
		move_ants(lem);
	}
	search_party(lem);
	while (lem->n_end)
	{	
		visualize(lem);
		move_ants(lem);
		search_party(lem);
	}
}

int		main(int argc, char **argv)
{
	t_lem	lem;
	t_room *room;

	set_zero(&lem);
	if (argc == 2)
		if (!strcmp(argv[1], "-v"))
			lem.visualizer = 1;
	ft_putnbr(lem.visualizer);
	count_ants(&lem);
	read_input(&lem);
	assign_values(&lem, lem.end);
	send_ants(&lem);
	room = lem.rooms_head;
	while (room)
	{
		ft_putstr("\n");
		ft_putstr(room->name);
		ft_putchar(' ');
		ft_putnbr(room->ant);
		ft_putchar(' ');
		room = room->next;
	}
	ft_putstr("\n");
	delmem(&lem, 0);
	return (0);
}
