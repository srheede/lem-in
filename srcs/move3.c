/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srheede <srheede@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 13:11:04 by srheede           #+#    #+#             */
/*   Updated: 2018/10/17 14:57:33 by srheede          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

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

void	result(t_lem *lem, t_send *send, t_room *tmp, t_room *curr)
{
	if (tmp && !lem->visualizer)
	{
		ft_putstr("L");
		if (curr == lem->start)
			ft_putnbr(send->count);
		else
			ft_putnbr(curr->ant);
		ft_putstr("-");
		ft_putstr(tmp->name);
		ft_putstr(" ");
	}
}

void	move3b(t_lem *lem, t_send *send, t_move *move)
{
	move->pos_new->next = linknew(move->room);
	move->pos_new = move->pos_new->next;
	lem->pos_new_last = move->pos_new;
	if (move->pos_ants)
	{
		move->tmp = (t_room *)move->pos_ants->room;
		move->room = choose_room(lem, send, move->tmp);
	}
}

void	move3a(t_lem *lem, t_send *send, t_move *move)
{
	move->pos_new = linknew(move->tmp);
	lem->pos_new = move->pos_new;
	lem->pos_new_last = move->pos_new;
	lem->pos_ants = move->pos_new;
	move->pos_ants = move->pos_ants->next;
	if (move->pos_ants)
	{
		move->tmp = (t_room *)move->pos_ants->room;
		move->room = choose_room(lem, send, move->tmp);
	}
}

void	move3(t_lem *lem, t_send *send, t_move *move)
{
	move->tmp = (t_room *)move->pos_ants->room;
	move->room = choose_room(lem, send, move->tmp);
	if (!move->room && !move->pos_new)
		move3a(lem, send, move);
	else if (!move->room && move->pos_new)
		move3b(lem, send, move);
	else if (move->room != lem->end && move->pos_new)
	{
		move->pos_new->next = linknew(move->room);
		move->pos_new = move->pos_new->next;
		lem->pos_new_last = move->pos_new;
	}
	else if (move->room != lem->end)
	{
		move->pos_new = linknew(move->room);
		lem->pos_new = move->pos_new;
		lem->pos_new_last = move->pos_new;
		lem->pos_ants = move->pos_new;
	}
}
