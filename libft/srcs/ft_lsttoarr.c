/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttoarr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srheede <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 10:18:09 by srheede           #+#    #+#             */
/*   Updated: 2018/06/15 07:47:11 by srheede          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**ft_lsttoarr(t_list *list)
{
	char	**arr;
	int		i;

	if (list)
	{
		arr = (char **)malloc(sizeof(char *) * ft_lstsize(list) + 1);
		if (!arr)
			return (NULL);
		i = 0;
		while (list->next)
		{
			arr[i] = ft_strndup(list->content, list->content_size);
			list = list->next;
			i++;
		}
		arr[i] = NULL;
		return (arr);
	}
	return (NULL);
}
