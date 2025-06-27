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

static inline int	stack_push(t_stack *stack, int elem)
{
	if (stack->size == MAX_STACK_SIZE)
		return (1);
	stack->elems[stack->size] = elem;
	++stack->size;
	return (0);
}

/* It is the caller's responsibility
 * to ensure that the stack contains
 * at least one element before popping */
static inline int	*stack_pop(t_stack *stack)
{
	return (&stack->elems[stack->size - 1]);
}

void stack_print(t_stack *stack)
{
	for (int i = 0; i < stack->size; ++i)
		printf("%d ", stack->elems[i]);
	printf("\n");
}

int	main(int argc, char **argv)
{
	t_stack	a;

	stack_init(&a);

	for (int i = 0; i < 10; ++i)
		stack_push(&a, i);

	stack_print(&a);

	for (int i = 0; i < 8; ++i)
		stack_pop(&a);

	stack_print(&a);

	int *elem = stack_pop(&a);
	printf("elem = %d\n", *elem);

	return (0);
}
