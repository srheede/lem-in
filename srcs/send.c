/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srheede <srheede@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 13:11:04 by srheede           #+#    #+#             */
/*   Updated: 2018/10/22 15:46:38 by srheede          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

t_room	*choose_room(t_lem *lem, t_send *send, t_room *current)
{
	t_choose	ch;

	ch.links = current->links_head;
	ch.tmp = NULL;
	if (current == lem->end)
		return (ch.tmp);
	while (ch.links)
	{
		ch.room = (t_room *)ch.links->room;
		if (ch.room == lem->end)
		{
			ch.tmp = ch.room;
			lem->n_end--;
			break ;
		}
		if (!ch.room->ant)
		{
			if ((!ch.tmp || ch.tmp->end > ch.room->end) && ch.room->end)
				ch.tmp = ch.room;
		}
		ch.links = ch.links->next;
	}
	result(lem, send, ch.tmp, current);
	return (ch.tmp);
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
