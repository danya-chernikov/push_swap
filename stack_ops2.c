#include "stack_basis.h"
#include "stack_ops.h"

/* If the stack contains N elements,
 * it swaps the elements at indexes
 * [N - 1] and [N - 2] */
void	stack_swap(t_operations *ops, t_stack *stack, const stack_type stype)
{
	int	tmp;

	tmp = stack->elems[stack->size - 1];
	stack->elems[stack->size - 1] = stack->elems[stack->size - 2];
	stack->elems[stack->size - 2] = tmp;
	stack->top = &stack->elems[stack->size - 1];
	if (stype == STACK_A)
		ops_add(ops, SA);
	else if (stype == STACK_B)
		ops_add(ops, SB);
}

void	stack_rotate(t_operations *ops, t_stack *stack, const stack_type stype)
{
	int		tmp;
	size_t	i;

	tmp = stack->elems[stack->size - 1];
	i = stack->size - 1;
	while (i > 0)
	{
		stack->elems[i] = stack->elems[i - 1];
		--i;
	}
	stack->elems[0] = tmp;
	stack->top = &stack->elems[stack->size - 1];
	if (stype == STACK_A)
		ops_add(ops, RA);
	else if (stype == STACK_B)
		ops_add(ops, RB);
}

void	stack_reverse_rotate(t_operations *ops, t_stack *stack,
			const stack_type stype)
{
	int		tmp;
	size_t	i;

	i = 0;
	tmp = stack->elems[0];
	while (i < stack->size)
	{
		stack->elems[i] = stack->elems[i + 1];
		++i;
	}
	stack->elems[stack->size - 1] = tmp;
	stack->top = &stack->elems[stack->size - 1];
	if (stype == STACK_A)
		ops_add(ops, RRA);
	else if (stype == STACK_B)
		ops_add(ops, RRB);
}

/* Takes the top element of stack `b`
 * and places it on top of stack `a` */
void	stack_push_a(t_operations *ops, t_stack *a, t_stack *b)
{
	int	*top_b;
	
	top_b = stack_pop(b);
	stack_push(a, *top_b);
	ops_add(ops, PA);
}

/* Takes the top element of stack `a`
 * and places it on top of stack `b` */
void	stack_push_b(t_operations *ops, t_stack *a, t_stack *b)
{
	int	*top_a;

	top_a = stack_pop(a);
	stack_push(b, *top_a);
	ops_add(ops, PB);
}
