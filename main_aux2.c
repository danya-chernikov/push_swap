/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_aux2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:55:44 by dchernik          #+#    #+#             */
/*   Updated: 2025/09/21 14:19:08 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "packer.h"
#include "main_aux.h"
#include "libft.h"
#include <unistd.h>

/* Inits both A and B stacks and copies input arguments into A */
int	init_stacks(t_stack *a, t_stack *b, int *arr, size_t elems_num)
{
	if (!stack_init(a, elems_num))
		return (0);
	array_copy(a->sorted, arr, elems_num);
	if (!stack_init(b, elems_num))
	{
		stack_free(a);
		return (0);
	}
	return (1);
}

/* Parse argv[1] if it contains the string with all the arguments to sort */
int	check_string_arg(char ***nums_to_sort, char **argv,
		int argc, int *f_string_arg)
{
	if (argc == 2)
	{
		if (!is_number(argv[1]))
		{
			*f_string_arg = 1;
			*nums_to_sort = split_string_arg(argv);
			if (!(*nums_to_sort))
				return (0);
		}
	}
	return (1);
}

char	**det_args_source(char **nums_to_sort, size_t *elems_num,
			char **argv, void **pack)
{
	char	**args_src;
	int		argc;
	int		f_string_arg;

	argc = *(int *)pack[0];
	f_string_arg = *(int *)pack[1];
	args_src = NULL;
	if (f_string_arg)
	{
		*elems_num = get_str_args_size(nums_to_sort);
		args_src = nums_to_sort;
	}
	else
	{
		*elems_num = argc - 1;
		args_src = argv + 1;
	}
	free(pack);
	return (args_src);
}

int	launch_sort(t_operations *ops, t_stack *a, t_stack *b, size_t elems_num)
{
	if (elems_num == 2)
	{
		sort_two(ops, a);
	}
	else if (elems_num == 3)
	{
		sort_three(ops, a);
	}
	else if (elems_num == 4)
	{
		if (!sort_four(ops, a, b))
			return (0);
	}
	else if (elems_num > 4)
	{
		if (!sort_common(ops, a, b))
			return (0);
	}
	return (1);
}
