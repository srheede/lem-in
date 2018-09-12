/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srheede <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 00:36:00 by srheede           #+#    #+#             */
/*   Updated: 2018/06/15 07:48:09 by srheede          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strndup(char *src, size_t n)
{
	char	*dst;
	size_t	len;

	if (!src)
		return (NULL);
	len = ft_strlen(src);
	if (n > len)
		n = len;
	dst = (char *)malloc(sizeof(char) * n + 1);
	if (dst)
		ft_strncpy(dst, src, n);
	return (dst);
}
