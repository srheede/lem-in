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

void	move4(t_lem *lem, t_move *move)
{
	move->pos_new = linknew(move->room);
	lem->pos_new = move->pos_new;
	lem->pos_ants = move->pos_new;
}

void	move2(t_lem *lem, t_send *send, t_move *move)
{
	move->pos_new = linknew(move->tmp);
	lem->pos_new = move->pos_new;
	lem->pos_ants = move->pos_new;
	move->pos_ants = move->pos_ants->next;
	move->tmp = (t_room *)move->pos_ants->room;
	move->room = choose_room(lem, send, move->tmp);
}

void	move1(t_lem *lem, t_send *send, t_move *move)
{
	move->pos_new = NULL;
	move->pos_ants = lem->pos_ants;
	move->tmp = (t_room *)move->pos_ants->room;
	move->room = choose_room(lem, send, move->tmp);
}

int		move_ants(t_lem *lem, t_send *send)
{
	t_move	move;

	move1(lem, send, &move);
	if (!move.room && move.pos_ants->next)
		move2(lem, send, &move);
	else if (!move.room)
		return (0);
	while (move.room == lem->end && move.pos_ants->next)
	{
		move.room->ant = move.tmp->ant;
		move.tmp->ant = 0;
		move.tmp_node = move.pos_ants;
		move.pos_ants = move.pos_ants->next;
		if (move.pos_ants)
			move3(lem, send, &move);
	}
	if (!move.pos_new)
		move4(lem, &move);
	move5(lem, send, &move);
	return (0);
}
