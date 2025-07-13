/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 12:16:50 by dchernik          #+#    #+#             */
/*   Updated: 2025/07/13 16:06:22 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "libft.h"
#include "auxiliary.h"
#include "args_parser.h"
#include "stack_basis.h"
#include "quick_sort.h"
#include "sorting.h"

#define ERROR_MSG	"Error\n"

int	main(int argc, char **argv)
{
	int				*arr;
	t_stack			a;
	t_stack			b;
	t_operations	ops;

	size_t			elems_num;
	int				f_string_arg;
	char			**nums_to_sort;
	char			**args;

	f_string_arg = 0;
	args = NULL;
	nums_to_sort = NULL;
	if (argc == 1)
		exit(1);

	/* Parse argv[1] if it contains the string with all the arguments to sort */
	if (argc == 2)
	{
		if (!is_number(argv[1]))
		{
			f_string_arg = 1;
			nums_to_sort = split_string_arg(argv);
			if (!nums_to_sort)
				return (0);
		}
	}

	/* Check input elements for validity */
	if (f_string_arg)
	{
		elems_num = get_str_args_size(nums_to_sort);
		args = nums_to_sort;
	}
	else
	{
		elems_num = argc - 1;
		args = argv;
	}

	if (!check_ints_validity(argc, args))
	{
		write(STDERR_FILENO, ERROR_MSG, ft_strlen(ERROR_MSG));
		if (f_string_arg)
			string_args_free(nums_to_sort);
		exit(2);
	}

	/* Allocate the array for input data of stack A */
	arr = (int *)malloc(elems_num * sizeof (int));
	if (!arr)
	{
		write(STDERR_FILENO, ERROR_MSG, ft_strlen(ERROR_MSG));
		if (f_string_arg)
			string_args_free(nums_to_sort);
		exit(3);
	}
	/* Sort input elements and check them for duplicates */
	if (f_string_arg)
		array_copy_atoi(arr, args, 0, elems_num);
	else
		array_copy_atoi(arr, args, 1, elems_num);
	quick_sort(arr, 0, elems_num - 1);
	if (!check_duplicates(arr, elems_num))
	{
		write(STDERR_FILENO, ERROR_MSG, ft_strlen(ERROR_MSG));
		free(arr);
		if (f_string_arg)
			string_args_free(nums_to_sort);
		exit(4);
	}

	/* Init stack A */
	if (!stack_init(&a, elems_num))
	{
		write(STDERR_FILENO, ERROR_MSG, ft_strlen(ERROR_MSG));
		free(arr);
		if (f_string_arg)
			string_args_free(nums_to_sort);
		exit(5);
	}
	/* Copy sorted array of input elements into A */
	array_copy(a.sorted, arr, elems_num);
	/* Init stack B */
	if (!stack_init(&b, elems_num))
	{
		write(STDERR_FILENO, ERROR_MSG, ft_strlen(ERROR_MSG));
		stack_free(&a);
		free(arr);
		if (f_string_arg)
			string_args_free(nums_to_sort);
		exit(6);
	}

	/* Copy input elements into stack A */
	args_to_stack(&a, elems_num, args, f_string_arg);

	/* Free string args */
	if (f_string_arg)
		string_args_free(nums_to_sort);

	/* Check if the input element sequence was initially sorted */
	if (stack_sorted(&a))
	{
		stack_free(&a);
		stack_free(&b);
		free(arr);
		exit(7);
	}

	/* Inititialize the array of operations */
	if (!ops_init(&ops))
	{
		write(STDERR_FILENO, ERROR_MSG, ft_strlen(ERROR_MSG));
		stack_free(&a);
		stack_free(&b);
		free(arr);
		exit(8);
	}

	/* Perform sorting */
	if (elems_num == 2)
	{
		sort_two(&ops, &a);
	}
	else if (elems_num == 3)
	{
		sort_three(&ops, &a);
	}
	else if (elems_num == 4)
	{
		if (!sort_four(&ops, &a, &b))
		{
			write(STDERR_FILENO, ERROR_MSG, ft_strlen(ERROR_MSG));
			ops_free(&ops);
			stack_free(&a);
			stack_free(&b);
			free(arr);
			exit(9);
		}
	}
	else if (elems_num > 4)
	{
		if (!sort_common(&ops, &a, &b))
		{
			write(STDERR_FILENO, ERROR_MSG, ft_strlen(ERROR_MSG));
			ops_free(&ops);
			stack_free(&a);
			stack_free(&b);
			free(arr);
			exit(10);
		}
	}

	/*
	ft_printf("\nAfter sorting\n\n");
	ft_printf("a | ");
	stack_print(&a);
	ft_printf("b | ");
	stack_print(&b);*/

	/* Optimize */
	if (!remove_paired_r_rr(&ops) || !substitute_r_rr(&ops) || !substitute_s_ss(&ops))
	{
		write(STDERR_FILENO, ERROR_MSG, ft_strlen(ERROR_MSG));
		ops_free(&ops);
		stack_free(&a);
		stack_free(&b);
		free(arr);
		exit(11);
	}

	ops_print(&ops);

	/* Let's do some extra checking. We'll determine if it's
	 * possible to sort the array using the reduced list of
	 * operations. If it's not, we'll know that an error
	 * occurred during the optimization process, and we'll
	 * simply print the original (non-reduced) list */
	

	/* Free all the staff */
	ops_free(&ops);
	stack_free(&a);
	stack_free(&b);
	free(arr);
	return (0);
}
