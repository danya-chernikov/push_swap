#if !defined(STACK_BASIS_H)
# define STACK_BASIS_H

#include <stddef.h>

#define MAX_STACK_SIZE	1024

/*  [0]   [1]   [2]   [3]   [4]   [5]  <-- array indexes
 * [150] [355] [-42] [ 0 ] [124] [813] <-- elements
 *   | 							   |
 *	 v							   v
 * bottom						  top */
typedef struct	s_stack
{
	int		*elems; // must be on heap
	int		*top;
	int		*bottom;
	size_t	size;
	size_t	capacity;
}	t_stack;

int		stack_init(t_stack *stack, const size_t capacity);
void	stack_free(t_stack *stack);
void	stack_print(t_stack *stack);
void	stack_push(t_stack *stack, const int elem);
int		*stack_pop(t_stack *stack);
int		stack_empty(t_stack *stack);
int		stack_sorted(t_stack *stack);

#endif
