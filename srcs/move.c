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

#include "../lem-in.h"



int		move_ants(t_lem *lem)
{
	t_move	move;

	move.pos_new = NULL;
	move.pos_ants = lem->pos_ants;
	move.tmp = (t_room *)move.pos_ants->room;
	move.room = choose_room(lem, move.tmp);
	if (!move.room && move.pos_ants->next)
	{
		move.pos_new = linknew(move.tmp);
		lem->pos_new = move.pos_new;
		lem->pos_ants = move.pos_new;
		move.pos_ants = move.pos_ants->next;
		move.tmp = (t_room *)move.pos_ants->room;
		move.room = choose_room(lem, move.tmp);
	}
	else if (!move.room)
		return (0);
	while (move.room == lem->end && move.pos_ants->next)
	{
		move.room->ant = move.tmp->ant;
		move.tmp->ant = 0;
		move.tmp_node = move.pos_ants;
		move.pos_ants = move.pos_ants->next;
		if (move.pos_ants)
		{
			move.tmp = (t_room *)move.pos_ants->room;
			move.room = choose_room(lem, move.tmp);
			if (!move.room && !move.pos_new)
			{
				move.pos_new = linknew(move.tmp);
				lem->pos_new = move.pos_new;
				lem->pos_ants = move.pos_new;	
				move.pos_ants = move.pos_ants->next;
				if (move.pos_ants)
				{
					move.tmp = (t_room *)move.pos_ants->room;
					move.room = choose_room(lem, move.tmp);
				}
			}
			else if (!move.room && move.pos_new)
			{
				move.pos_new->next = linknew(move.room);
				move.pos_new = move.pos_new->next;
				lem->pos_new_last = move.pos_new;
				if (move.pos_ants)
				{
					move.tmp = (t_room *)move.pos_ants->room;
					move.room = choose_room(lem, move.tmp);
				}
			}
			else if (move.room != lem->end && move.pos_new)
			{
				move.pos_new->next = linknew(move.room);
				move.pos_new = move.pos_new->next;
				lem->pos_new_last = move.pos_new;
			}
			else if (move.room != lem->end)
			{
				move.pos_new = linknew(move.room);
				lem->pos_new = move.pos_new;
				lem->pos_ants = move.pos_new;
			}
		}		
	}
	if (!move.pos_new)
	{
		move.pos_new = linknew(move.room);
		lem->pos_new = move.pos_new;
		lem->pos_ants = move.pos_new;
	}
	while (move.pos_ants)
	{
		move.room->ant = move.tmp->ant;
		move.tmp->ant = 0;
		move.tmp_node = move.pos_ants;
		move.pos_ants = move.pos_ants->next;
		if (move.pos_ants)
		{
			move.tmp = (t_room *)move.pos_ants->room;
			move.room = choose_room(lem, move.tmp);
			if (!move.room)
			{
				move.pos_new->next = linknew(move.tmp);
				move.pos_new = move.pos_new->next;
				lem->pos_new_last = move.pos_new;			
				free(move.tmp_node);
				break ;
			}
			if (move.room != lem->end)
			{
				move.pos_new->next = linknew(move.room);
				move.pos_new = move.pos_new->next;
				lem->pos_new_last = move.pos_new;
			}
		}
		free(move.tmp_node);
	}
	return (0);
}