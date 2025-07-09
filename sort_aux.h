#if !defined(SORT_AUX_H)
# define SORT_AUX_H

#include "stack_basis.h"

int		check_swap(t_stack *stack);
int		r_til_sorted(t_stack *stack);
int		rr_til_sorted(t_stack *stack);
void	move_elem_to_top(t_stack *stack, int elem);

#endif
