/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srheede <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 13:11:04 by srheede           #+#    #+#             */
/*   Updated: 2018/08/29 17:55:29 by srheede          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	move5a(t_move *move)
{
	move->room->ant = move->tmp->ant;
	move->tmp->ant = 0;
	move->tmp_node = move->pos_ants;
	move->pos_ants = move->pos_ants->next;
}

void	move5(t_lem *lem, t_send *send, t_move *move)
{
	while (move->pos_ants)
	{
		move5a(move);
		if (move->pos_ants)
		{
			move->tmp = (t_room *)move->pos_ants->room;
			move->room = choose_room(lem, send, move->tmp);
			if (!move->room)
			{
				move->pos_new->next = linknew(move->tmp);
				move->pos_new = move->pos_new->next;
				lem->pos_new_last = move->pos_new;
				free(move->tmp_node);
				break ;
			}
			if (move->room != lem->end)
			{
				move->pos_new->next = linknew(move->room);
				move->pos_new = move->pos_new->next;
				lem->pos_new_last = move->pos_new;
			}
		}
		free(move->tmp_node);
	}
}
