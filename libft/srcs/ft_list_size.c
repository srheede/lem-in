/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srheede <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 00:41:38 by srheede           #+#    #+#             */
/*   Updated: 2018/06/07 01:20:31 by srheede          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		ft_lstsize(t_list *list)
{
	int	i;

	if (list)
	{
		i = 0;
		while (list)
		{
			i++;
			list = list->next;
		}
		return (i);
	}
	return (0);
}
