/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliary2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:22:23 by dchernik          #+#    #+#             */
/*   Updated: 2025/07/14 15:22:24 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "auxiliary.h"

int	array_sorted(const int *arr, const size_t size)
{
	size_t	i;

	i = 0;
	while (i < size - 1)
	{
		if (arr[i] > arr[i + 1])
			return (0);
		++i;
	}
	return (1);
}

void	array_copy(int *arr_dst, const int *arr_src, const size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		arr_dst[i] = arr_src[i];
		++i;
	}
}

void	array_copy_atoi(int *arr_dst, char **arr_src,
			const size_t src_spos, const size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		arr_dst[i] = ft_atoi(arr_src[src_spos + i]);
		++i;
	}
}

void	print_n_times(const char *str, const size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		ft_printf("%s", str);
		++i;
	}
}

/* Returns index of the number in the array. If the number
 * wasn't found returns 0 */
size_t	array_get_elem_index(const int *arr, const size_t size,
			const int number)
{
	size_t	ind;

	ind = 0;
	while (ind < size)
	{
		if (arr[ind] == number)
			return (ind);
		++ind;
	}
	return (0);
}
