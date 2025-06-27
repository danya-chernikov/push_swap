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

void				stack_init(t_stack *stack);
void				stack_print(t_stack *stack);
static inline void	stack_push(t_stack *stack, int elem);
static inline int	*stack_pop(t_stack *stack);

/* Operations from task's announcement */
static inline void	stack_swap(t_stack *stack);
static inline void	stack_reverse(t_stack *stack);
static inline void	stack_reverse_rotate(t_stack *stack);

int	main(int argc, char **argv)
{
	t_stack	a;

	stack_init(&a);

	for (int i = 0; i < 10; ++i)
		stack_push(&a, i);

	stack_print(&a);

	/*for (int i = 0; i < 8; ++i)
		stack_pop(&a);*/

	stack_swap(&a);

	stack_print(&a);

	printf("\n");

	for (int i = 0; i < 5; ++i)
	{
		stack_reverse(&a);
		stack_print(&a);
	}

	printf("\n");

	for (int i = 0; i < 5; ++i)
	{
		stack_reverse_rotate(&a);
		stack_print(&a);
	}

	int *elem = stack_pop(&a);
	printf("elem = %d\n", *elem);

	stack_print(&a);

	return (0);
}

void	stack_init(t_stack *stack)
{
	stack->top = NULL;
	stack->bottom = NULL;
	stack->size = 0;
}

void	stack_print(t_stack *stack)
{
	for (int i = 0; i < stack->size; ++i)
		printf("%d ", stack->elems[i]);
	printf("\n");
}

/* It's the caller's responsibility to ensure
 * the stack size does not exceed MAX_STACK_SIZE */
static inline void	stack_push(t_stack *stack, int elem)
{
	stack->elems[stack->size] = elem;
	++stack->size;
}

/* It's the caller's responsibility
 * to ensure that the stack contains
 * at least one element before popping */
static inline int	*stack_pop(t_stack *stack)
{
	int	*elem = &stack->elems[stack->size - 1];
	--stack->size;
	return (elem);
}

/* If the stack contains N elements,
 * it swaps the elements at indexes
 * [N - 1] and [N - 2] */
static inline void	stack_swap(t_stack *stack)
{
	int	tmp;

	tmp = stack->elems[stack->size - 1];
	stack->elems[stack->size - 1] = stack->elems[stack->size - 2];
	stack->elems[stack->size - 2] = tmp;
}

static inline void	stack_reverse(t_stack *stack)
{
	int	tmp;

	tmp = stack->elems[stack->size - 1];
	for (int i = stack->size - 1; i > 0; --i)
		stack->elems[i] = stack->elems[i - 1];
	stack->elems[0] = tmp;
}

static inline void	stack_reverse_rotate(t_stack *stack)
{
	int	tmp;

	tmp = stack->elems[0];
	for (int i = 0; i < stack->size; ++i)
		stack->elems[i] = stack->elems[i + 1];
	stack->elems[stack->size - 1] = tmp;
}
