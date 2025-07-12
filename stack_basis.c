/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_basis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 12:16:59 by dchernik          #+#    #+#             */
/*   Updated: 2025/07/12 12:17:00 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stack_basis.h"

#include <stdlib.h>

int	stack_init(t_stack *stack, const size_t capacity)
{
	stack->elems = (int *)malloc(capacity * sizeof (int));
	if (!stack->elems)
		return (0);
	stack->sorted = (int *)malloc(capacity * sizeof (int));
	if (!stack->sorted)
		return (0);
	stack->capacity = capacity;
	stack->size = 0;
	stack->top = NULL;
	return (1);
}

void	stack_free(t_stack *stack)
{
	free(stack->elems);
	free(stack->sorted);
	stack->elems = NULL;
	stack->sorted = NULL;
	stack->capacity = 0;
	stack->size = 0;
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
	stack->top = &stack->elems[stack->size];
	++stack->size;
}

/* It's the caller's responsibility
 * to ensure that the stack contains
 * at least one element before popping */
int	*stack_pop(t_stack *stack)
{
	int	*elem;
	
	elem = &stack->elems[stack->size - 1];
	stack->top = &stack->elems[stack->size - 1];
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
