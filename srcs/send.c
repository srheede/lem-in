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

t_room	*choose_room(t_lem *lem, t_send *send, t_room *current)
{
	t_links *links;
	t_room	*room;
	t_room	*tmp;

	links = current->links_head;
	tmp = NULL;
	if (current == lem->end)
		return (tmp);
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
	if (tmp && !lem->visualizer)
	{
		ft_putstr("L");
		if (current == lem->start)
			ft_putnbr(send->count);
		else
			ft_putnbr(current->ant);
		ft_putstr("-");
		ft_putstr(tmp->name);
		ft_putstr(" ");
	}
	return (tmp);
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

void	send_ants_end(t_lem *lem, t_send *send)
{
	while (lem->end->ant != lem->n_total)
	{
		if (!lem->visualizer)
			ft_putstr("\n");
		visualize(lem);
		move_ants(lem, send);
	}
	search_party(lem);
	while (lem->n_end)
	{
		if (!lem->visualizer)
			ft_putstr("\n");
		visualize(lem);
		move_ants(lem, send);
		search_party(lem);
	}
}

int		send_while(t_lem *lem, t_send *send)
{
	while (send->room)
	{
		send->room->ant = send->count;
		send->count++;
		lem->n_ants--;
		if (!lem->n_ants)
			return (0);
		send->room = choose_room(lem, send, lem->start);
		if (!send->room)
			return (0);
		send->pos_ants->next = linknew(send->room);
		send->pos_ants = send->pos_ants->next;
	}
	return (0);
}

void	send_ants(t_lem *lem)
{
	t_send	send;

	send.count = 1;
	while (lem->n_ants)
	{
		send.room = choose_room(lem, &send, lem->start);
		send.pos_ants = linknew(send.room);
		lem->pos_ants = send.pos_ants;
		send_while(lem, &send);
		if (lem->pos_new)
		{
			send.pos_ants = lem->pos_ants;
			lem->pos_ants = lem->pos_new;
			lem->pos_new_last->next = send.pos_ants;
		}
		visualize(lem);
		if (!lem->visualizer)
			ft_putstr("\n");
		move_ants(lem, &send);
	}
	send_ants_end(lem, &send);
	if (!lem->visualizer)
		ft_putstr("\n");
}
