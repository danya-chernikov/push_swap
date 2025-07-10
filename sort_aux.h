#if !defined(SORT_AUX_H)
# define SORT_AUX_H

#include "stack_basis.h"

int		check_swap(t_stack *stack);
size_t	r_til_sorted(t_stack *stack);
size_t	rr_til_sorted(t_stack *stack);
void	move_elem_to_top(t_stack *stack, int elem);

#endif
