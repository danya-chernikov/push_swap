#if !defined(SORT_AUX_H)
# define SORT_AUX_H

#include "stack_basis.h"
#include "stack_ops.h"

int		check_swap(t_operations *ops, t_stack *stack);
size_t	r_til_sorted(t_operations *ops, t_stack *stack);
size_t	rr_til_sorted(t_operations *ops, t_stack *stack);

void	move_elem_to_top(t_operations *ops,
			t_stack *stack, stack_type stype, int elem);

#endif
