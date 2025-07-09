#if !defined(STACK_OPS_H)
# define STACK_OPS_H

#include "stack_basis.h"

typedef enum { SA, SB, PA, PB, RA, RB, RRA, RRB } ops;

/* Operations from task's announcement */
void	stack_swap(t_stack *stack);
void	stack_rotate(t_stack *stack);
void	stack_rotate_n_times(t_stack *stack, const size_t n);
void	stack_reverse_rotate(t_stack *stack);
void	stack_reverse_rotate_n_times(t_stack *stack, const size_t n);
void	stack_push_a(t_stack *a, t_stack *b);
void	stack_push_b(t_stack *a, t_stack *b);

#endif
