#include "main_aux.h"

int	sorting(t_operations *ops, t_stack *a, t_stack *b, size_t elems_num)
{
	/* Check if the input element sequence was initially sorted */
	if (!stack_sorted(a))
	{
		/* Inititialize the array of operations */
		if (!ops_init(ops))
			return (0);	
		if (!launch_sort(ops, a, b, elems_num) || !remove_paired_r_rr(ops) ||
				!substitute_r_rr(ops) || !substitute_s_ss(ops))
		{
			ops_free(ops);
			return (0);
		}
	}
	return (1);
}

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
		args_src = argv;
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
