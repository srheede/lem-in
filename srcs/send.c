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

void	send_ants_end(t_lem *lem)
{
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
}
