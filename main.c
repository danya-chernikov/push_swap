#include <unistd.h>
#include <stdlib.h>

#include "libft.h"
#include "args_parser.h"
#include "stack_basis.h"
#include "sorting.h"

#define ERROR_MSG	"Error\n"

int	main(int argc, char **argv)
{
	t_stack	a;
	t_stack	b;

	if (argc == 1)
		exit(1);

	if (!check_ints_validity(argc, argv))
	{
		write(2, ERROR_MSG, ft_strlen(ERROR_MSG));
		exit(2);
	}

	if (!stack_init(&a, argc - 1))
	{
		write(2, ERROR_MSG, ft_strlen(ERROR_MSG));
		exit(2);
	}	
	if (!stack_init(&b, argc - 1))
	{
		write(2, ERROR_MSG, ft_strlen(ERROR_MSG));
		exit(2);
	}	

	args_to_stack(&a, argc, argv);

	ft_printf("a | ");
	stack_print(&a);

	ft_printf("b | ");
	stack_print(&b);

	if (argc == 3)
		sort_two(&a);
	else if (argc == 4)
		sort_three(&a);
	else if (argc == 5)
		sort_four(&a, &b);
	else
		sort_common(&a, &b);

	stack_free(&a);
	stack_free(&b);
	return (0);
}
