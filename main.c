#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft.h"
#include "quick_sort.h"

#define MAX_STACK_SIZE	1024

/*  [0]   [1]   [2]   [3]   [4]   [5]  <-- array indexes
 * [150] [355] [-42] [ 0 ] [124] [813] <-- elements
 *   | 							   |
 *	 v							   v
 * bottom						  top */

typedef struct	s_stack
{
	int		elems[MAX_STACK_SIZE]; // must be on heap
	int		*top;
	int		*bottom;
	size_t	size;
}	t_stack;

#define NO_ARGS_ERR	"Usage\n\t%s <top element> ... <bottom element>\n"

enum ops { SA, SB, PA, PB, RA, RB, RRA, RRB };

void				sort_three(t_stack *stack);

void				stack_init(t_stack *stack);
void				stack_print(t_stack *stack);
static inline void	stack_push(t_stack *stack, int elem);
static inline int	*stack_pop(t_stack *stack);
static inline int	is_stack_empty(t_stack *stack);

/* Operations from task's announcement */
static inline void	stack_swap(t_stack *stack);
static inline void	stack_reverse(t_stack *stack);
static inline void	stack_reverse_rotate(t_stack *stack);
void				stack_push_a(t_stack *a, t_stack *b);
void				stack_push_b(t_stack *a, t_stack *b);

int					is_array_sorted(int *arr, int size);

int	main(int argc, char **argv)
{
	const char *ops_strs[8] = { "sa", "sb", "pa", "pb", "ra", "rb", "rra", "rrb" };

	t_stack	a;
	t_stack	b;

	int		argv0_len;

	argv0_len = ft_strlen(argv[0]);
	if (argc == 1)
	{
		write(2, NO_ARGS_ERR, ft_strlen(NO_ARGS_ERR) + argv0_len);
		exit(1);
	}

	printf("kekekek\n");

	return (0);
}

/* Sorts the stack consiting of
 * three arbitrary elements
 * performing minimum possible
 * amount of operations. If the
 * stack is already sorted does
 * nothing */
void	sort_three(t_stack *stack)
{
	// | 2 10 5 <-top
	if (stack->elems[0] < stack->elems[1] &&
		stack->elems[1] > stack->elems[2] &&
		stack->elems[0] < stack->elems[2])
	{
		stack_reverse_rotate(stack);
		printf("rra\n");
	}

	// | 5 2 10
	if (stack->elems[0] > stack->elems[1] &&
		stack->elems[1] < stack->elems[2] &&
		stack->elems[0] < stack->elems[2])
	{
		stack_reverse(stack);
		printf("ra\n");
	}

	// | 5 10 2
	if (stack->elems[0] < stack->elems[1] &&
		stack->elems[1] > stack->elems[2] &&
		stack->elems[0] > stack->elems[2])
	{
		stack_reverse_rotate(stack);
		stack_swap(stack);
		printf("rra\n");
		printf("sa\n");
	}
	
	// | 10 2 5
	if (stack->elems[0] > stack->elems[1] &&
		stack->elems[1] < stack->elems[2] &&
		stack->elems[0] > stack->elems[2])
	{
		stack_swap(stack);
		printf("sa\n");
	}

	// | 2 5 10	worst case
	if (stack->elems[0] < stack->elems[1] &&
		stack->elems[1] < stack->elems[2] &&
		stack->elems[0] < stack->elems[2])
	{
		stack_swap(stack);
		stack_reverse_rotate(stack);
		printf("sa\n");
		printf("rra\n");
	}
}

void	stack_init(t_stack *stack)
{
	stack->top = NULL;
	stack->bottom = NULL;
	stack->size = 0;
}

void	stack_print(t_stack *stack)
{
	for (size_t i = 0; i < stack->size; ++i)
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

static inline int	is_stack_empty(t_stack *stack)
{
	if (stack->size == 0)
		return (0);
	return (1);
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
	for (size_t i = 0; i < stack->size; ++i)
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

/* Checks if the array is sorted in
 * ascending order */
int	is_array_sorted(int *arr, int size)
{
	for (int i = 0; i < size - 1; ++i)
	{
		if (arr[i] > arr[i + 1])
			return (0);
	}
	return (1);
}

// 2^64 = 18446744073709551616
// 8^21 = 18014398509481984000
// 8^10 = 1073741824
