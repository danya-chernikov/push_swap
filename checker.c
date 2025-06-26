#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE	1024

/*  [0]   [1]   [2]   [3]   [4]   [5]  <-- array indexes
 * [150] [355] [-42] [ 0 ] [124] [813] <-- elements
 *   | 							   |
 *	 v							   v
 * bottom						  top */

typedef struct s_stack
{
	int		elems[MAX_STACK_SIZE];
	int		*top;
	int		*bottom;
	size_t	size;
}	t_stack;

void	stack_init(t_stack *stack)
{
	stack->top = NULL;
	stack->bottom = NULL;
	stack->size = 0;
}

int	push(t_stack *stack, int elem)
{
	if (stack->size == MAX_STACK_SIZE)
		return (1);
	stack->elems[stack->size] = elem;
	return (0);
}

/* It is the caller's responsibility
 * to ensure that the stack contains
 * at least one element before popping */
int	*pop(t_stack *stack)
{
	return (&stack->elems[size - 1]);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		exit (EXIT_FAILURE);
	}

	t_stack	a;
	stack_init(&a);

	return (0);
}
