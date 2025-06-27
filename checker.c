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
void				stack_push_a(t_stack *a, t_stack *b);
void				stack_push_b(t_stack *a, t_stack *b);

int	main(int argc, char **argv)
{
	t_stack	a;
	t_stack	b;

	stack_init(&a);
	stack_init(&b);

	stack_push(&a, 8);
	stack_push(&a, 5);
	stack_push(&a, 6);
	stack_push(&a, 3);
	stack_push(&a, 1);
	stack_push(&a, 2);

	printf("a | ");
	stack_print(&a);
	printf("b | ");
	stack_print(&b);
	printf("\n");

	printf("Exec sa:\n");
	stack_swap(&a);
	printf("a | ");
	stack_print(&a);
	printf("b | ");
	stack_print(&b);
	printf("\n");

	printf("Exec pb pb pb:\n");
	stack_push_b(&a, &b);
	stack_push_b(&a, &b);
	stack_push_b(&a, &b);
	printf("a | ");
	stack_print(&a);
	printf("b | ");
	stack_print(&b);
	printf("\n");

	printf("Exec ra rb:\n");
	stack_reverse(&a);
	stack_reverse(&b);
	printf("a | ");
	stack_print(&a);
	printf("b | ");
	stack_print(&b);
	printf("\n");

	printf("Exec rra rrb:\n");
	stack_reverse_rotate(&a);
	stack_reverse_rotate(&b);
	printf("a | ");
	stack_print(&a);
	printf("b | ");
	stack_print(&b);
	printf("\n");

	printf("Exec sa:\n");
	stack_swap(&a);
	printf("a | ");
	stack_print(&a);
	printf("b | ");
	stack_print(&b);
	printf("\n");

	printf("Exec pa pa pa:\n");
	stack_push_a(&a, &b);
	stack_push_a(&a, &b);
	stack_push_a(&a, &b);
	printf("a | ");
	stack_print(&a);
	printf("b | ");
	stack_print(&b);

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

/* Takes the top element of stack `b`
 * and places it on top of stack `a` */
void	stack_push_a(t_stack *a, t_stack *b)
{
	int	*top_b;
	
	top_b = stack_pop(b);
	stack_push(a, *top_b);
}

/* Takes the top element of stack `a`
 * and places it on top of stack `b` */
void	stack_push_b(t_stack *a, t_stack *b)
{
	int	*top_a;

	top_a = stack_pop(a);
	stack_push(b, *top_a);
}
