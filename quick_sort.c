/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 12:16:56 by dchernik          #+#    #+#             */
/*   Updated: 2025/07/13 13:53:10 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quick_sort.h"

#include <stddef.h>

static void		swap(int *a, int *b);
static size_t	partition(int *arr, int low, int high);

void	quick_sort(int *arr, int low, int high)
{
	int	pivot_ind;

	if (low < high)
	{
		pivot_ind = partition(arr, low, high);
		quick_sort(arr, low, pivot_ind - 1);
		quick_sort(arr, pivot_ind + 1, high);
	}
}

static void	swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static size_t	partition(int *arr, int low, int high)
{
	int	pivot;
	int	i;
	int	j;

	j = low;
	i = low - 1;
	pivot = arr[high];
	while (j <= high - 1)
	{
		if (arr[j] < pivot)
		{
			i++;
			swap(&arr[i], &arr[j]);
		}
		j++;
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}
