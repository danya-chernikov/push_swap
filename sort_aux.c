#include "sort_aux.h"
#include "stack_ops.h"
#include "auxiliary.h"
#include "libft.h"

#include <stdlib.h>

/* Checks whether applying a
 * swap operation leads to the
 * stack being sorted */
int		check_swap(t_stack *stack)
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
 * returns -1. This function does not
 * check if the stack is sorted or not */
int		r_til_sorted(t_stack *stack)
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
	if (sorted_f)
	{
		free(cstack.elems);
		return (ops_cnt);
	}
	free(cstack.elems);
	return (0);
}

int		rr_til_sorted(t_stack *stack)
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
	if (sorted_f)
	{
		free(cstack.elems);
		return (ops_cnt);
	}
	free(cstack.elems);
	return (0);
}

/* Moves the element to the top of the stack by
 * executing either ra or rra consecutively in the
 * most efficient way */
void	move_elem_to_top(t_stack *stack, int elem)
{
	size_t	elem_ind;

	elem_ind = stack_get_elem_index(stack, elem);
	if (elem_ind > 0) /* elem_ind == 0 means element is already on top */
	{
		if (elem_ind <= stack->size / 2)
		{
			stack_rotate_n_times(stack, elem_ind);
			print_n_times("ra\n", elem_ind);
		}
		else
		{
			stack_reverse_rotate_n_times(stack, stack->size - elem_ind);
			print_n_times("rra\n", stack->size - elem_ind);
		}
	}
}
