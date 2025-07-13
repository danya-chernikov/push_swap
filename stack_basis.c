/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_basis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 12:16:59 by dchernik          #+#    #+#             */
/*   Updated: 2025/07/13 14:05:51 by dchernik         ###   ########.fr       */
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
