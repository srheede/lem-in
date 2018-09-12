/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srheede <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 17:50:16 by srheede           #+#    #+#             */
/*   Updated: 2018/08/29 17:55:26 by srheede          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem-in.h"

int		check_flag(char *str)
{
	int	err;

	err = 0;
	if (!ft_strcmp(str, ""))
		err++;
	if (!err)
		return (0);
	return (1);
}

int		error_check(int argc, char **argv)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		if (check_arg(argc, argv, argv[i]))
			return (1);
		i++;
	}
	return (0);
}
