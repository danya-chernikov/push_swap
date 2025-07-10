#if !defined(SORTING_H)
# define SORTING_H

#include "stack_basis.h"
#include "stack_ops.h"

void	sort_two(t_operations *ops, t_stack *stack);
void	sort_three(t_operations *ops, t_stack *stack);
int		sort_four(t_operations *ops, t_stack *a, t_stack *b);
int		sort_common(t_operations *ops, t_stack *a, t_stack *b);

#endif
