/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srheede <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 13:11:04 by srheede           #+#    #+#             */
/*   Updated: 2018/08/29 17:55:29 by srheede          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem-in.h"

void	count_ants(t_lem *lem)
{
	get_next_line(0, &lem->buffer);
	lem->number = ft_itoa(ft_atoi(lem->buffer));
	if (strcmp(lem->buffer, lem->number) || ft_atoi(lem->buffer) < 1)
		delmem(lem, 1);
	lem->n_ants = ft_atoi(lem->buffer);
	lem->n_end = lem->n_ants;
	lem->n_total = lem->n_ants;
	ft_putnbr(lem->n_ants);
	ft_putchar('\n');
	ft_strdel(&lem->number);
	ft_strdel(&lem->buffer);
}

t_links	*linknew(t_room *room)
{
	t_links *links;

	links = (t_links *)malloc(sizeof(t_links));
	links->room = room;
	links->next = NULL;
	return (links);
}

void	create_link(t_room *first, t_room *second)
{
	int		err;
	t_links	*tmp;

	err = 0;
	if (!first->links)
	{
		first->links = linknew(second);
		first->links_head = first->links;
	}
	else
	{
		tmp = first->links_head;
		while (tmp)
		{
			if (tmp->room == second)
				err++;
			tmp = tmp->next;
		}
		if (!err)
		{
			first->links->next = linknew(second);
			first->links = first->links->next;
		}
	}
}

void	assign_link(t_lem *lem, char **arr, t_room *tmp, t_room *first)
{
	if (!lem->rooms_head)
		delmem(lem, 1);
	tmp = lem->rooms_head;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, arr[0]))
		{
			first = tmp;
			break ;
		}
		tmp = tmp->next;
	}
	tmp = lem->rooms_head;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, arr[1]))
			break ;
		tmp = tmp->next;
	}
	if (tmp && first)
	{
		create_link(first, tmp);
		create_link(tmp, first);
		ft_putstr(lem->buffer);
		ft_putchar('\n');
	}
}

void	assign_links(t_lem *lem)
{
	char	**arr;
	t_room	*tmp;
	t_room	*first;

	arr = ft_strsplit(lem->buffer, '-');
	tmp = NULL;
	first = NULL;
	if (ft_arrlen(arr) == 2)
		assign_link(lem, arr, tmp, first);
	ft_arrdel(arr);
}
