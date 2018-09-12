/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srheede <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 17:42:02 by srheede           #+#    #+#             */
/*   Updated: 2018/06/01 10:26:06 by srheede          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;
	int		i;

	if (s)
	{
		if (start > ft_strlen(s))
			return (NULL);
		sub_str = ft_strnew(len + 1);
		if (!sub_str)
			return (NULL);
		i = 0;
		while (len-- && s[start] != '\0')
		{
			sub_str[i++] = s[start];
			start++;
		}
		sub_str[i] = '\0';
		return (sub_str);
	}
	return (NULL);
}
