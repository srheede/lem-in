/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srheede <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 09:46:55 by srheede           #+#    #+#             */
/*   Updated: 2018/08/28 09:48:25 by srheede          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		*ft_arrdup(const int *src, size_t len)
{
	int *dst;

	dst = (int *)malloc(sizeof(int) * len);
	if (dst)
		ft_arrcpy(dst, src, len);
	return (dst);
}
