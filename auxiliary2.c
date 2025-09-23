/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliary2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:22:23 by dchernik          #+#    #+#             */
/*   Updated: 2025/09/23 14:37:42 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "auxiliary.h"

/* Checks if the number is in range of [INT_MIN; INT_MAX] */
int	num_in_range(const char *num, const int left, const int right)
{
	long long	number;

	number = ft_atoll(num);
	if (number < left || number > right)
		return (0);
	return (1);
}

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
