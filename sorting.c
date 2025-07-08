#include "sorting.h"
#include "sort_aux.h"
#include "libft.h"
#include "stack_ops.h"
#include "auxiliary.h"

void	sort_two(t_stack *stack)
{
	stack_swap(stack);
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
		ft_printf("rra\n");
	}

	// | 5 2 10
	if (stack->elems[0] > stack->elems[1] &&
		stack->elems[1] < stack->elems[2] &&
		stack->elems[0] < stack->elems[2])
	{
		stack_reverse(stack);
		ft_printf("ra\n");
	}

	// | 5 10 2
	if (stack->elems[0] < stack->elems[1] &&
		stack->elems[1] > stack->elems[2] &&
		stack->elems[0] > stack->elems[2])
	{
		stack_reverse_rotate(stack);
		stack_swap(stack);
		ft_printf("rra\n");
		ft_printf("sa\n");
	}
	
	// | 10 2 5
	if (stack->elems[0] > stack->elems[1] &&
		stack->elems[1] < stack->elems[2] &&
		stack->elems[0] > stack->elems[2])
	{
		stack_swap(stack);
		ft_printf("sa\n");
	}

	// | 2 5 10	worst case
	if (stack->elems[0] < stack->elems[1] &&
		stack->elems[1] < stack->elems[2] &&
		stack->elems[0] < stack->elems[2])
	{
		stack_swap(stack);
		stack_reverse_rotate(stack);
		ft_printf("sa\n");
		ft_printf("rra\n");
	}
}

/* First, we try rotating three times and
 * reverse rotating three times to see if
 * the array gets sorted. If not, we push
 * the top element of stack A into stack B,
 * sort stack A, determine the element in A
 * on top of which the element from B should
 * be placed, move that element to the top
 * of A using ra or rra (in the most efficient
 * way, of course), push the element from B
 * back onto the top of A, and finally ra or
 * rra stack A until it is sorted */
void	sort_four(t_stack *a, t_stack *b)
{
	int	ops_num;

	ops_num = r_til_sorted(a);
	if (ops_num)
	{
		print_n_times("ra", ops_num);
	}
	else
	{
		ops_num = rr_til_sorted(a);
		if (ops_num)
			print_n_times("rra", ops_num);
	}
	if (!ops_num)
	{
		stack_push_b(a, b);
		sort_three(a);	
	}
}

void	sort_common(t_stack *a, t_stack *b)
{
	(void)a;
	(void)b;
}
