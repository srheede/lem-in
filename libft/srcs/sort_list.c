/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 12:23:23 by exam              #+#    #+#             */
/*   Updated: 2018/06/15 06:56:14 by srheede          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*sort_list(t_list *lst, int (*cmp)(int, int))
{
	t_list	*begin;
	int		i;

	begin = lst;
	i = 0;
	while (lst->next)
	{
		if (!cmp(lst->data, lst->next->data))
		{
			ft_swap(&lst->data, &lst->next->data);
			i++;
		}
		lst = lst->next;
	}
	if (i)
		begin = sort_list(begin, cmp);
	return (begin);
}
