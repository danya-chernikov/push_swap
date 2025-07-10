#include "stack_basis.h"
#include "stack_ops.h"
#include "libft.h"

#include <stdlib.h>

int		ops_init(t_operations *ops)
{
	ops->size = 0;
	ops->capacity = OPS_LIST_INC_CHUNK_SIZE;
	ops->arr = (ops_type *)malloc(ops->capacity * sizeof (ops_type));
	if (!ops->arr)
		return (0);
	return (1);
}

void	ops_free(t_operations *ops)
{
	ops->capacity = 0;
	ops->size = 0;
	free(ops->arr);
	ops->arr = NULL;
}

void	ops_add(t_operations *ops, ops_type op)
{
	ops->arr[ops->size] = op;
	++(ops->size);
}

void	ops_remove(t_operations *ops, size_t index)
{
	size_t	i;

	// add optimization
	i = index;
	while (i < ops->size - 1)
	{
		ops->arr[i] = ops->arr[i + 1];
		++i;
	}
	--(ops->size);
}

void	print_op_by_type(ops_type op)
{
	if (op == SA)
		ft_printf("%s\n", SA_OP_STR);
	if (op == SB)
		ft_printf("%s\n", SB_OP_STR);
	if (op == SS)
		ft_printf("%s\n", SS_OP_STR);
	if (op == PA)
		ft_printf("%s\n", PA_OP_STR);
	if (op == PB)
		ft_printf("%s\n", PB_OP_STR);
	if (op == RA)
		ft_printf("%s\n", RA_OP_STR);
	if (op == RB)
		ft_printf("%s\n", RB_OP_STR);
	if (op == RR)
		ft_printf("%s\n", RR_OP_STR);
	if (op == RRA)
		ft_printf("%s\n", RRA_OP_STR);
	if (op == RRB)
		ft_printf("%s\n", RRB_OP_STR);
	if (op == RRR)
		ft_printf("%s\n", RRR_OP_STR);
}

void	ops_print(t_operations *ops)
{
	size_t	i;

	i = 0;
	while (i < ops->size)
	{
		print_op_by_type(ops->arr[i]);
		++i;
	}
}

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
	if (stype == A)
		ops_add(ops, SA);
	else if (stype == B)
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
	if (stype == A)
		ops_add(ops, RA);
	else if (stype == B)
		ops_add(ops, RB);
}

void	stack_reverse_rotate(t_operations *ops, t_stack *stack, const stack_type stype)
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
	if (stype == A)
		ops_add(ops, RRA);
	else if (stype == B)
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

void	stack_rotate_n_times(t_operations *ops, t_stack *stack, const stack_type stype, const size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		stack_rotate(ops, stack, stype);
		++i;
	}
}

void	stack_reverse_rotate_n_times(t_operations *ops, t_stack *stack, const stack_type stype, const size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		stack_reverse_rotate(ops, stack, stype);
		++i;
	}
}
