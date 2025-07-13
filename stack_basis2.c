#include "libft.h"
#include "stack_basis.h"

#include <stdlib.h>

int	stack_empty(t_stack *stack)
{
	if (stack->size == 0)
		return (0);
	return (1);
}

int	stack_sorted(t_stack *stack)
{
	int	i;

	i = stack->size - 1;
	while (i > 0)
	{
		if (stack->elems[i] > stack->elems[i - 1])
			return (0);
		--i;
	}
	return (1);
}

int	stack_contains(t_stack *stack, int elem)
{
	size_t	i;

	i = 0;
	while (i < stack->size)
	{
		if (stack->elems[i] == elem)
			return (1);
		++i;
	}
	return (0);
}

int	stack_copy(t_stack *dst, t_stack *src)
{
	size_t	i;

	dst->size = src->size;
	dst->capacity = src->capacity;
	dst->elems = (int *)malloc(dst->capacity * sizeof (int));
	if (!dst->elems)
		return (0);
	i = 0;
	while (i < dst->size)
	{
		dst->elems[i] = src->elems[i];
		++i;
	}
	dst->top = &dst->elems[dst->size - 1];
	return (1);
}

/* If there is no element in the stack returns -1 */
long long	stack_get_elem_index(t_stack *stack, int elem)
{
	size_t	i;

	i = 0;
	while (i < stack->size)
	{
		if (stack->elems[stack->size - i - 1] == elem)
			return (i);
		++i;
	}
	return (-1);
}
