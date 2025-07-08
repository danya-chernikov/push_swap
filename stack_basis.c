#include "libft.h"
#include "stack_basis.h"

#include <stdlib.h>

int	stack_init(t_stack *stack, const size_t capacity)
{
	stack->elems = (int *)malloc(capacity * sizeof (int));
	if (!stack->elems)
		return (0);
	stack->capacity = capacity;
	stack->size = 0;
	stack->bottom = NULL;
	stack->top = NULL;
	return (1);
}

void	stack_free(t_stack *stack)
{
	free(stack->elems);
	stack->elems = NULL;
	stack->capacity = 0;
	stack->size = 0;
	stack->bottom = NULL;
	stack->top = NULL;
}

void	stack_print(t_stack *stack)
{
	size_t	i;

	i = 0;
	while (i < stack->size)
	{
		ft_printf("%d ", stack->elems[i]);
		++i;
	}
	ft_printf("\n");
}

/* It's the caller's responsibility to ensure
 * the stack size does not exceed MAX_STACK_SIZE */
void	stack_push(t_stack *stack, const int elem)
{
	stack->elems[stack->size] = elem;
	++stack->size;
}

/* It's the caller's responsibility
 * to ensure that the stack contains
 * at least one element before popping */
int	*stack_pop(t_stack *stack)
{
	int	*elem;
	
	elem = &stack->elems[stack->size - 1];
	--stack->size;
	return (elem);
}

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
