#include "sort_aux.h"
#include "stack_ops.h"
#include "libft.h"

#include <stdlib.h>

/* Checks whether applying a
 * swap operation leads to the
 * stack being sorted */
int	check_swap(t_stack *stack)
{
	t_stack	cstack;

	if (!stack_copy(&cstack, stack))
		return (-1);
	stack_swap(&cstack);
	if (stack_sorted(&cstack))
	{
		free(cstack.elems);
		return (1);
	}
	free(cstack.elems);
	return (0);
}

/* Performs the rotate operation
 * on the stack until it is sorted.
 * If the stack becomes sorted after
 * applying n operations, it returns
 * n; otherwise, it returns 0. Of
 * course, we don’t want to change
 * the original stack — we are just
 * performing a kind of test. If an
 * error during stack copying occured
 * returns -1 */
int	r_til_sorted(t_stack *stack)
{
	int		sorted_f;
	size_t	ops_cnt;
	t_stack	cstack;

	ops_cnt = 0;
	sorted_f = 0;
	if (!stack_copy(&cstack, stack))
		return (-1);
	while (ops_cnt < cstack.size - 1)
	{
		stack_rotate(&cstack);
		++ops_cnt;
		if (stack_sorted(&cstack))
		{
			sorted_f = 1;
			break ;
		}
	}
	ft_printf("r_til_sorted(): ops_cnt = %u\n", ops_cnt);
	if (sorted_f)
	{
		free(cstack.elems);
		return (ops_cnt);
	}
	free(cstack.elems);
	return (0);
}

int	rr_til_sorted(t_stack *stack)
{
	int		sorted_f;
	size_t	ops_cnt;
	t_stack	cstack;

	ops_cnt = 0;
	sorted_f = 0;
	if (!stack_copy(&cstack, stack))
		return (-1);
	while (ops_cnt < cstack.size - 1)
	{
		stack_reverse_rotate(&cstack);
		++ops_cnt;
		if (stack_sorted(&cstack))
		{
			sorted_f = 1;
			break ;
		}
	}
	ft_printf("rr_til_sorted(): ops_cnt = %u\n", ops_cnt);
	if (sorted_f)
	{
		free(cstack.elems);
		return (ops_cnt);
	}
	free(cstack.elems);
	return (0);
}
