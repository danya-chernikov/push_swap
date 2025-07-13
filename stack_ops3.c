#include "stack_basis.h"
#include "stack_ops.h"

void	stack_rotate_n_times(t_operations *ops, t_stack *stack,
			const stack_type stype, const size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		stack_rotate(ops, stack, stype);
		++i;
	}
}

void	stack_reverse_rotate_n_times(t_operations *ops, t_stack *stack,
			const stack_type stype, const size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		stack_reverse_rotate(ops, stack, stype);
		++i;
	}
}
