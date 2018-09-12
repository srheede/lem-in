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
	lem->debug = 0;
}

void	read_flags(int argc, char **argv, t_lem *lem)
{
	int		i;

	i = 1;
	set_zero(lem);
	while (i < argc)
	{
		if (!ft_strcmp(argv[i], "-d"))
			lem->debug = 1;
		i++;
	}
}

void	delmem(t_lem *lem, int err)
{
	if (lem->debug)
		free(lem->debug);
	if (err)
		ft_putstr("Error\n");
}

int		main(int argc, char **argv)
{
	t_lem	lem;

	if (argc > 1)
	{
		read_flags(argc, argv, &lem);
		if (!lem.file)
		{
			if (error_check(argc, argv) || read_input(argc, argv, &lem))
			{
				delmem(&lem, 1);
				return (-1);
			}
		}
		else
		{
			if (!read_file(argv[1], &lem))
			{
				delmem(&lem, 1);
				return (-1);
			}
		}
		sort(&lem);
		delmem(&lem, 0);
	}
	return (0);
}
