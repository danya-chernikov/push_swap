/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 12:17:32 by dchernik          #+#    #+#             */
/*   Updated: 2025/07/13 18:24:33 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "auxiliary.h"
#include "args_parser.h"

#include <limits.h>
#include <stdlib.h>

int		check_ints_validity(int argc, char **argv)
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

int		is_number(const char *num)
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
int		check_duplicates(const int *arr, const size_t size)
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

char	**split_string_arg(char **argv)
{
	size_t	i;
	size_t	arg_i;
	size_t	num_i;
	size_t	num_cnt;
	size_t	args_arr_capacity;
	char	**nums_to_sort;

	args_arr_capacity = ARGS_INC_CHUNK_SIZE;
	nums_to_sort = (char **)malloc((args_arr_capacity + 1) * sizeof (char *));
	if (!nums_to_sort)
		return (NULL);
	i = 0;
	while (i < args_arr_capacity + 1)
	{
		nums_to_sort[i] = (char *)malloc(MAX_INT_STR_LEN * sizeof (char));
		if (!nums_to_sort[i])
			return (NULL);
		++i;
	}

	arg_i = 0;
	num_cnt = 0;
	while (arg_i < ft_strlen(argv[1]))
	{
		if (argv[1][arg_i] != ' ')
		{
			num_i = 0;
			while ((argv[1][arg_i] != ' ') && (arg_i < ft_strlen(argv[1])))
			{
				if (num_i > MAX_INT_STR_LEN)
					return (NULL);
				nums_to_sort[num_cnt][num_i] = argv[1][arg_i];
				++arg_i;
				++num_i;
			}
			nums_to_sort[num_cnt][num_i] = '\0';
			++num_cnt;
		}
		++arg_i;
	}
	nums_to_sort[num_cnt] = NULL;

	/*ft_printf("\nnums_to_sort:\n");
	for (size_t i = 0; i < num_cnt; ++i)
	{
		for (size_t j = 0; nums_to_sort[i][j] != '\0'; ++j)
			ft_printf("%c", nums_to_sort[i][j]);
		ft_printf("\n");
	}
	ft_printf("\n");*/
	return (nums_to_sort);
}

void	string_args_free(char **str_args)
{
	size_t	i;

	i = 0;
	while (str_args[i] != NULL)
	{
		free(str_args[i]);
		++i;
	}
	free(str_args);
}
