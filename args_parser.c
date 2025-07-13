/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 12:17:32 by dchernik          #+#    #+#             */
/*   Updated: 2025/07/13 23:22:50 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "auxiliary.h"
#include "args_parser.h"

#include <limits.h>
#include <stdlib.h>

int	check_ints_validity(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_number(argv[i]) || !num_in_range(argv[i], INT_MIN, INT_MAX))
			return (0);
		++i;
	}
	return (1);
}

int	is_number(const char *num)
{
	size_t	i;

	if ((num[0] != '-') && !ft_isdigit((num[0])))
		return (0);
	if ((num[0] == '-') && (num[1] == '0'))
		return (0);
	if ((num[0] == '-') && (ft_strlen(num) == 1))
		return (0);
	if ((num[0] == '0') && (ft_strlen(num) > 1))
		return (0);
	i = 1;
	while (i < ft_strlen(num))
	{
		if (!ft_isdigit(num[i]))
			return (0);
		++i;
	}
	return (1);
}

/* Returns 1 if no duplicate elements were found
 * in the sorted array */
int	check_duplicates(const int *arr, const size_t size)
{
	size_t	i;

	i = 0;
	while (i < size - 1)
	{
		if (arr[i] == arr[i + 1])
			return (0);
		++i;
	}
	return (1);
}

void	args_to_stack(t_stack *stack, size_t elems_num,
			char **args, int f_string_arg)
{
	long long	i;
	long long	beg_ind;

	if (f_string_arg)
	{
		beg_ind = 0;
		i = elems_num - 1;
	}
	else
	{
		beg_ind = 1;
		i = elems_num;
	}
	while (i >= beg_ind)
	{
		stack_push(stack, ft_atoi(args[i]));
		--i;
	}
}

size_t	get_str_args_size(char **args)
{
	size_t	size;

	size = 0;
	while (args[size] != NULL)
		++size;
	return (size);
}
