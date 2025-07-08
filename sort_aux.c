#include "sort_aux.h"
#include "stack_ops.h"

/* Performs `reverse` operation on the stack
 * until it will be sorted. If stack was sorted
 * as a result of applying n operations it returns n,
 * if not returns 0 */
int	r_til_sorted(t_stack *stack)
{
	int		sorted_f;
	size_t	ops_cnt;

	sorted_f = 0;
	ops_cnt = 0;
	while (ops_cnt < stack->size - 1)
	{
		stack_reverse(stack);
		if (stack_sorted(stack))
		{
			sorted_f = 1;
			break ;
		}
		++ops_cnt;
	}
	if (sorted_f)
		return (ops_cnt);
	return (0);
}

int	rr_til_sorted(t_stack *stack)
{
	int		sorted_f;
	size_t	ops_cnt;

	sorted_f = 0;
	ops_cnt = 0;
	while (ops_cnt < stack->size - 1)
	{
		stack_reverse_rotate(stack);
		if (stack_sorted(stack))
		{
			sorted_f = 1;
			break ;
		}
		++ops_cnt;
	}
	if (sorted_f)
		return (ops_cnt);
	return (0);
}
