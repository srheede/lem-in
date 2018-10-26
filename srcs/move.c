/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srheede <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 13:11:04 by srheede           #+#    #+#             */
/*   Updated: 2018/08/29 17:55:29 by srheede          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int		move_ants(t_lem *lem, t_send *send)
{
	t_room			*room;
	t_room			*tmp;
	t_links			*pos_ants;
	t_links			*pos_new;
	t_links			*tmp_node;

	pos_new = NULL;
	pos_ants = lem->pos_ants;
	tmp = (t_room *)pos_ants->room;
	room = choose_room(lem, send, tmp);
	if (!room && pos_ants->next)
	{
		pos_new = linknew(tmp);
		lem->pos_new = pos_new;
		lem->pos_ants = pos_new;
		pos_ants = pos_ants->next;
		tmp = (t_room *)pos_ants->room;
		room = choose_room(lem, send, tmp);
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
			room = choose_room(lem, send, tmp);
			if (!room && !pos_new)
			{
				pos_new = linknew(tmp);
				lem->pos_new = pos_new;
				lem->pos_ants = pos_new;
				pos_ants = pos_ants->next;
				if (pos_ants)
				{
					tmp = (t_room *)pos_ants->room;
					room = choose_room(lem, send, tmp);
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
					room = choose_room(lem, send, tmp);
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
			room = choose_room(lem, send, tmp);
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
