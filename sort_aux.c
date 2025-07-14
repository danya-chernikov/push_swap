/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 12:17:28 by dchernik          #+#    #+#             */
/*   Updated: 2025/07/14 15:18:49 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort_aux.h"
#include "auxiliary.h"
#include "libft.h"

#include <stdlib.h>

/* sort_four() */

/* +++ */
int	sort_four_alg(t_operations *ops, t_stack *a, t_stack *b)
{
	size_t	i;

	i = 0;
	while (i < a->capacity)
	{
		if (a->sorted[i] == *b->top)
		{
			if (i == a->capacity - 1)
			{
				stack_push_a(ops, a, b);
				stack_rotate(ops, a, STACK_A);
			}
			else
				sort_four_bring_back_to_a(ops, a, b, &i);
			if (!stack_sorted(a))
			{
				if (rotate_stack_until_sorted(ops, a, STACK_A) < 0)
					return (0);
			}
			break ;
		}
		++i;
	}
	return (1);
}

/* +++ */
void	sort_four_bring_back_to_a(t_operations *ops, t_stack *a, t_stack *b, size_t *i)
{
	++(*i);
	while ((*i < a->capacity) && (!stack_contains(a, a->sorted[*i])))
		++(*i);
	if (*i < a->capacity)
	{
		move_elem_to_top(ops, a, STACK_A, a->sorted[*i]);
		stack_push_a(ops, a, b);
	}
	else
	{
		stack_push_a(ops, a, b);
		stack_rotate(ops, a, STACK_A);
	}
}

/* Checks whether applying a swap operation results
 * in the stack being sorted. This function does not
 * modify the stack, so we pass `NOP` as the operation
 * to perform */
/* +++ */
int	check_swap(t_operations *ops, t_stack *stack)
{
	t_stack	cstack;

	if (!stack_copy(&cstack, stack))
		return (-1);
	stack_swap(ops, &cstack, NOP);
	if (stack_sorted(&cstack))
	{
		free(cstack.elems);
		return (1);
	}
	free(cstack.elems);
	return (0);
}

/* Performs the rotate operation on the stack until it is
 * sorted. If the stack becomes sorted after applying `n`
 * operations, it returns `n`; otherwise, it returns 0. Of
 * course, we don’t want to change the original stack — we
 * are just performing a kind of test. If an error during
 * stack copying occured returns -1. This function does
 * not check if the stack is sorted or not */
/* +++ */
size_t	r_til_sorted(t_operations *ops, t_stack *stack)
{
	int		sorted_f;
	size_t	ops_cnt;
	t_stack	cstack;

	ops_cnt = 0;
	sorted_f = 0;
	if (!stack_copy(&cstack, stack))
		return (-1);
	while (ops_cnt < cstack.size - 1)
	{
		stack_rotate(ops, &cstack, NOP);
		++ops_cnt;
		if (stack_sorted(&cstack))
		{
			sorted_f = 1;
			break ;
		}
	}
	if (sorted_f)
	{
		free(cstack.elems);
		return (ops_cnt);
	}
	free(cstack.elems);
	return (0);
}

/* This function does not change the stack */
/* +++ */
size_t	rr_til_sorted(t_operations *ops, t_stack *stack)
{
	int		sorted_f;
	size_t	ops_cnt;
	t_stack	cstack;

	ops_cnt = 0;
	sorted_f = 0;
	if (!stack_copy(&cstack, stack))
		return (-1);
	while (ops_cnt < cstack.size - 1)
	{
		stack_reverse_rotate(ops, &cstack, NOP);
		++ops_cnt;
		if (stack_sorted(&cstack))
		{
			sorted_f = 1;
			break ;
		}
	}
	if (sorted_f)
	{
		free(cstack.elems);
		return (ops_cnt);
	}
	free(cstack.elems);
	return (0);
}
