/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 12:16:50 by dchernik          #+#    #+#             */
/*   Updated: 2025/07/13 05:24:12 by dchernik         ###   ########.fr       */
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
	size_t			elems_num;
	int				*arr;
	t_stack			a;
	t_stack			b;
	t_operations	ops;

	if (argc == 1)
		exit(1);

/*#ifdef DEBUG	
	FILE	*fp_tests;
	char	file_path[256];

	ft_printf("Enter the path to the file with tests: ");
	if (fgets(file_path, sizeof (file_path), stdin) != NULL)
	{
		file_path[strcspn(file_path, "\n")] = '\0';
		fp_tests = fopen(file_path, "r");
		if (!fp_tests)
			exit(1);

	}
	else
		exit(1);

#endif*/

	/* Check input elements for validity */
	elems_num = argc - 1;
	if (!check_ints_validity(argc, argv))
	{
		write(STDERR_FILENO, ERROR_MSG, ft_strlen(ERROR_MSG));
		exit(2);
	}

	/* Allocate the array for input data of stack A */
	arr = (int *)malloc(elems_num * sizeof (int));
	if (!arr)
	{
		write(STDERR_FILENO, ERROR_MSG, ft_strlen(ERROR_MSG));
		exit(3);
	}
	/* Sort input elements and check them for duplicates */
	array_copy_atoi(arr, argv, 1, elems_num);
	quick_sort(arr, 0, elems_num - 1);
	if (!check_duplicates(arr, elems_num))
	{
		write(STDERR_FILENO, ERROR_MSG, ft_strlen(ERROR_MSG));
		free(arr);
		exit(4);
	}

	/* Init stack A */
	if (!stack_init(&a, elems_num))
	{
		write(STDERR_FILENO, ERROR_MSG, ft_strlen(ERROR_MSG));
		free(arr);
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
		exit(6);
	}

	/* Copy input elements into stack A */
	args_to_stack(&a, argc, argv);
	/* Check if the input element sequence was initially sorted */
	if (stack_sorted(&a))
	{
		ft_printf("Already sorted. Do nothing\n");
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

	/* Print unsorted stacks */
	ft_printf("\nBefore sorting\n\n");
	ft_printf("a | ");
	stack_print(&a);
	ft_printf("b | ");
	stack_print(&b);

	/* Perform sorting */
	ft_printf("\nOperations:\n");
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

	/* Print sorted stacks */
	ft_printf("\nAfter sorting\n\n");
	ft_printf("a | ");
	stack_print(&a);
	ft_printf("b | ");
	stack_print(&b);

	/* Print the operations performed to sort the stacks */
	ft_printf("\nFull operations list:\n");
	ops_print(&ops);
	ft_printf("\nFull operations list size: %u\n", ops.size);

	/* Remove all unnecessary rotate repetitions */

	if (!remove_paired_r_rr(&ops) || !substitute_r_rr(&ops) || !substitute_s_ss(&ops))
	{
		write(STDERR_FILENO, ERROR_MSG, ft_strlen(ERROR_MSG));
		ops_free(&ops);
		stack_free(&a);
		stack_free(&b);
		free(arr);
		exit(11);
	}

	/* Print the operations performed to sort the stacks */
	ft_printf("\nReduced operations list:\n");
	ops_print(&ops);
	ft_printf("\nReduced operations list size: %u\n", ops.size);

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
