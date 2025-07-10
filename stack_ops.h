#if !defined(STACK_OPS_H)
# define STACK_OPS_H

#include "stack_basis.h"

/* This is the number that will be added
 * to each newly allocated memory size
 * for the list of operations when there
 * is not enough memory to accommodate
 * new operations. In other words, it is
 * the amount by which the size of the
 * ops_list array will be increased during
 * each subsequent memory reallocation */
#define OPS_LIST_INC_CHUNK_SIZE	8192

typedef enum { SA, SB, PA, PB, RA, RB, RRA, RRB } ops;

typedef struct s_operations
{
	size_t	arr_size;
	size_t	cnt;
	ops		*arr;
}	t_operations;


int		operaitons_init(t_operations *ops);
int		operaitons_free(t_operations *ops);

/* Operations from task's announcement */
void	stack_swap(t_operations *ops, t_stack *stack);
void	stack_rotate(t_operations *ops, t_stack *stack);
void	stack_reverse_rotate(t_operations *ops, t_stack *stack);
void	stack_push_a(t_operations *ops, t_stack *a, t_stack *b);
void	stack_push_b(t_operations *ops, t_stack *a, t_stack *b);

void	stack_rotate_n_times(t_operations *ops,
			t_stack *stack, const size_t n);

void	stack_reverse_rotate_n_times(t_operations *ops,
			t_stack *stack, const size_t n);

#endif
