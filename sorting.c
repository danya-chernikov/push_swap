#include "sorting.h"
#include "libft.h"
#include "stack_ops.h"

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

void	sort_four(t_stack *a, t_stack *b)
{
	(void)a;
	(void)b;
}

void	sort_common(t_stack *a, t_stack *b)
{
	(void)a;
	(void)b;
}
