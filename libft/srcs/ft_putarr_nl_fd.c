/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putarr_nl_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srheede <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 14:08:42 by srheede           #+#    #+#             */
/*   Updated: 2018/06/20 14:12:14 by srheede          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putarr_nl_fd(char **arr, int fd)
{
	while (*arr)
	{
		ft_putstr_fd(*arr, fd);
		ft_putchar_fd('\n', fd);
		arr++;
	}
}
