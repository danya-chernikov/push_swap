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
	int		*arr;
	size_t	elems_num;
	t_stack	a;
	t_stack	b;

	if (argc == 1)
		exit(1);

	/* Check input elements for validity */
	elems_num = argc - 1;
	if (!check_ints_validity(argc, argv))
	{
		write(STDERR_FILENO, ERROR_MSG, ft_strlen(ERROR_MSG));
		exit(2);
	}

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
		exit(4);
	}

	/* Init stack A */
	if (!stack_init(&a, elems_num))
	{
		write(STDERR_FILENO, ERROR_MSG, ft_strlen(ERROR_MSG));
		exit(5);
	}
	/* Copy sorted array of input elements into A */
	array_copy(a.sorted, arr, elems_num);
	/* Init stack B */
	if (!stack_init(&b, elems_num))
	{
		write(STDERR_FILENO, ERROR_MSG, ft_strlen(ERROR_MSG));
		exit(6);
	}

	/* Copy input elements into stack A */
	args_to_stack(&a, argc, argv);
	/* Check if the input element sequence was initially sorted */
	if (stack_sorted(&a))
	{
		ft_printf("Already sorted. Do nothing\n");
		exit(7);
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
		sort_two(&a);
	else if (elems_num == 3)
		sort_three(&a);
	else if (elems_num == 4)
		sort_four(&a, &b);
	else
		sort_common(&a, &b);

	/* Print sorted stacks */
	ft_printf("\nAfter sorting\n\n");
	ft_printf("a | ");
	stack_print(&a);
	ft_printf("b | ");
	stack_print(&b);

	/* Free all the staff */
	free(arr);
	stack_free(&a);
	stack_free(&b);
	return (0);
}
