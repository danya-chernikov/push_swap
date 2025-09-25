/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliary3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:56:24 by dchernik          #+#    #+#             */
/*   Updated: 2025/09/25 12:56:25 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "auxiliary.h"

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
