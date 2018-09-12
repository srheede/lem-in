/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srheede <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 08:25:00 by srheede           #+#    #+#             */
/*   Updated: 2018/08/28 08:58:48 by srheede          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	quicksort(int *arr, int first, int last)
{
	int i;
	int	j;
	int	pivot;

	if (first < last)
	{
		pivot = first;
		i = first;
		j = last;
		while (i < j)
		{
			while (arr[i] <= arr[pivot] && i < last)
				i++;
			while (arr[j] > arr[pivot])
				j--;
			if (i < j)
				ft_swap(&arr[i], &arr[j]);
		}
		ft_swap(&arr[pivot], &arr[j]);
		quicksort(arr, first, j - 1);
		quicksort(arr, j + 1, last);
	}
}
