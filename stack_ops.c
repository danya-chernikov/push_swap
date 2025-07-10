#include "stack_basis.h"
#include "stack_ops.h"
#include "libft.h"

int		operations_init(t_operations *ops)
{
	cnt = 0;
	arr_size = OPS_LIST_INC_CHUNK_SIZE;
	arr = (ops *)malloc(arr_size);
	if (!arr)
		return (0);
	return (1);
}

int		operations_free(t_operations *ops)
{
	arr_size = 0;
	cnt = 0;
	free(arr);
	arr = NULL;
}

int		operations_add(t_operations *ops, ops operation)
{
	ops->arr[cnt] = operation;
	++cnt;
}

int		operations_remove(t_operations *ops, size_t index)
{
	int	i;

	// add optimization
	i = index;
	while (i < cnt - 1)
	{
		
		++i;
	}
	--cnt;
}

/* If the stack contains N elements,
 * it swaps the elements at indexes
 * [N - 1] and [N - 2] */
void	stack_swap(t_stack *stack)
{
	int	tmp;

	tmp = stack->elems[stack->size - 1];
	stack->elems[stack->size - 1] = stack->elems[stack->size - 2];
	stack->elems[stack->size - 2] = tmp;
	stack->top = &stack->elems[stack->size - 1];
}

void	stack_rotate(t_stack *stack)
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
}

void	stack_rotate_n_times(t_stack *stack, const size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		stack_rotate(stack);
		++i;
	}
}

void	stack_reverse_rotate(t_stack *stack)
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
}

void	stack_reverse_rotate_n_times(t_stack *stack, const size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		stack_reverse_rotate(stack);
		++i;
	}
}

/* Takes the top element of stack `b`
 * and places it on top of stack `a` */
void	stack_push_a(t_stack *a, t_stack *b)
{
	int	*top_b;
	
	top_b = stack_pop(b);
	stack_push(a, *top_b);
}

/* Takes the top element of stack `a`
 * and places it on top of stack `b` */
void	stack_push_b(t_stack *a, t_stack *b)
{
	int	*top_a;

	top_a = stack_pop(a);
	stack_push(b, *top_a);
}
