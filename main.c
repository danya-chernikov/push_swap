#include <unistd.h>
#include <stdio.h>

#include "main_aux.h"
#include "libft.h"
#include "auxiliary.h"
#include "quick_sort.h"
#include "sorting.h"

int main(int argc, char **argv)
{
	int *arr;
	t_stack a;
	t_stack b;
	t_operations ops;

	int exit_code;
	size_t elems_num;
	int f_string_arg;
	char **nums_to_sort;
	char **args;

	exit_code = 0;
	/* PARSING PART */
	f_string_arg = 0;
	args = NULL;
	nums_to_sort = NULL;
	if (argc == 1)
		exit(1);

	if (!check_string_arg(&nums_to_sort, argv, argc, &f_string_arg))
		return (0);
	args = det_args_source(nums_to_sort, &elems_num, argv,
		pack_args(2, (void *)&argc, (void *)&f_string_arg));

	/* Check input elements for validity */
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

	if (!init_stacks(&a, &b, arr, elems_num))
	{
		write(STDERR_FILENO, ERROR_MSG, ft_strlen(ERROR_MSG));
		free(arr);
		if (f_string_arg)
			string_args_free(nums_to_sort);
		exit(6);
	}

	free(arr);

	/* Copy input elements into stack A */
	args_to_stack(&a, elems_num, args, f_string_arg);

	if (f_string_arg)
		string_args_free(nums_to_sort);

	/* SORTING PART */
	if (!sorting(&ops, &a, &b, elems_num))
	{
		write(STDERR_FILENO, ERROR_MSG, ft_strlen(ERROR_MSG));
		exit_code = 1;
	}

	/* Free all the staff */
	if (ops.f_exist)
		ops_free(&ops);
	stack_free(&a);
	stack_free(&b);
	return (exit_code);
}
