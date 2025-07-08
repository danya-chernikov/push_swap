#include <unistd.h>
#include <stdlib.h>

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
	int		i;
	t_stack	a;
	t_stack	b;

	if (argc == 1)
		exit(1);

	if (!check_ints_validity(argc, argv))
	{
		write(2, ERROR_MSG, ft_strlen(ERROR_MSG));
		exit(2);
	}

	arr = (int *)malloc((argc - 1) * sizeof (int));
	if (!arr)
	{
		write(2, ERROR_MSG, ft_strlen(ERROR_MSG));
		exit(3);
	}
	i = 1;
	while (i < argc)
	{
		arr[i - 1] = ft_atoi(argv[i]);
		++i;
	}
	quick_sort(arr, 0, argc - 2);
	if (!check_duplicates(arr, argc - 1))
	{
		write(2, ERROR_MSG, ft_strlen(ERROR_MSG));
		exit(4);
	}

	if (!stack_init(&a, argc - 1))
	{
		write(2, ERROR_MSG, ft_strlen(ERROR_MSG));
		exit(5);
	}	
	if (!stack_init(&b, argc - 1))
	{
		write(2, ERROR_MSG, ft_strlen(ERROR_MSG));
		exit(6);
	}

	i = 1;
	while (i < argc)
	{
		arr[i - 1] = ft_atoi(argv[i]);
		++i;
	}
	if (array_sorted(arr, argc - 1))
	{
		ft_printf("Already sorted. Do nothing\n");
		exit(7);
	}

	args_to_stack(&a, argc, argv);

	ft_printf("\nBefore sorting\n\n");
	ft_printf("a | ");
	stack_print(&a);

	ft_printf("b | ");
	stack_print(&b);

	ft_printf("\nOperations:\n");

	if (argc == 3)
		sort_two(&a);
	else if (argc == 4)
		sort_three(&a);
	else if (argc == 5)
		sort_four(&a, &b);
	else
		sort_common(&a, &b);

	ft_printf("\nAfter sorting\n\n");
	ft_printf("a | ");
	stack_print(&a);

	ft_printf("b | ");
	stack_print(&b);

	free(arr);
	stack_free(&a);
	stack_free(&b);
	return (0);
}
