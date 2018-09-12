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
	lem->start = NULL;
	lem->end = NULL;
	lem->buffer = NULL;
	lem->number = NULL;
	lem->n_ants = 0;
	lem->visualizer = 0;
}

void	delmem(t_lem *lem, int err)
{
	if (lem->arr)
		free(lem->arr);
	if (lem->buffer)
		ft_strdel(lem->buffer);
	if (lem->number)
		ft_strdel(lem->number);
	if (err)
		ft_putstr("Error\n");
	exit(0);
}

void	count_ants(t_lem *lem)
{
	get_next_line(0, &lem->buffer);
	lem->number = itoa(atoi(lem->buffer));
	if (!strcmp(lem->buffer, lem->number))
		delmem(&lem, 1);
	lem->n_ants = atoi(lem->buffer);
	ft_strdel(lem->number);
	ft_strdel(lem->buffer);
}

t_room	*ft_roomnew(char *name, int x, int y)
{
	t_room *room;

	room = (t_room *)malloc(sizeof(t_room));
	room->name = name;
	room->x = x;
	room->y = y;
	room->count = 0;
	room->distance = 0;
	room->links = NULL;
	room->next = NULL;
	return (room);
}

void	check_start(t_lem *lem)
{
	if (!ft_strcmp(lem->buffer, "##start"))
	{
		if (lem->start)
			delmem(&lem, 1);
		set_start(lem);
	}
	if (!ft_strcmp(lem->buffer, "##end"))
	{
		if (lem->end)
			delmem(&lem, 1);
		set_end(lem);
	}
}

void	create_room(t_lem *lem, char **arr)
{
	char	*x;
	char	*y;

	x = ft_itoa(ft_atoi(arr[1]));
	y = ft_itoa(ft_atoi(arr[2]));
	if (!ft_strcmp(arr[1], x) || !ft_strcmp(arr[2], y))
		delmem(lem, 1);
	ft_strdel(x);
	ft_strdel(y);
}

void	assign_link(t_lem *lem, char **arr)
{

}

void	read_input(t_lem *lem)
{
	char	**arr;

	count_ants(lem);
	while (get_next_line(0, &lem->buffer))
	{
		check_start(lem);
		arr = ft_strsplit(lem->buffer, ' ');
		if (ft_arrlen(arr) == 3)
			create_room(lem, arr);
		else if (ft_arrlen(arr) == 1)
			assign_link(lem, arr);
		ft_arrdel(arr);
		ft_strdel(lem->buffer);
	}
}

int		main(int argc, char **argv)
{
	t_lem	lem;

	set_zero(&lem);
	if (argc == 2)
		if (strcmp(argv[1], "-v"))
			lem.visualizer = 1;
	read_input(&lem);
	delmem(&lem, 0);
	return (0);
}
