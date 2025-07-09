#include "sort_aux.h"
#include "stack_ops.h"
#include "libft.h"

/* Performs the rotate operation
 * on the stack until it is sorted.
 * If the stack becomes sorted after
 * applying n operations, it returns
 * n; otherwise, it returns 0. Of
 * course, we don’t want to change
 * the original stack — we are just
 * performing a kind of test */
int	r_til_sorted(t_stack stack)
{
	int		sorted_f;
	size_t	ops_cnt;

	sorted_f = 0;
	ops_cnt = 0;
	while (ops_cnt < stack.size - 1)
	{
		stack_rotate(&stack);
		++ops_cnt;
		if (stack_sorted(&stack))
		{
			sorted_f = 1;
			break ;
		}
	}
	ft_printf("r_til_sorted(): ops_cnt = %u\n", ops_cnt);
	if (sorted_f)
		return (ops_cnt);
	return (0);
}

int	rr_til_sorted(t_stack stack)
{
	int		sorted_f;
	size_t	ops_cnt;

	sorted_f = 0;
	ops_cnt = 0;
	while (ops_cnt < stack.size - 1)
	{
		stack_reverse_rotate(&stack);
		++ops_cnt;
		if (stack_sorted(&stack))
		{
			sorted_f = 1;
			break ;
		}
	}
	ft_printf("rr_til_sorted(): ops_cnt = %u\n", ops_cnt);
	if (sorted_f)
		return (ops_cnt);
	return (0);
}
