/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_aux6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:24:31 by dchernik          #+#    #+#             */
/*   Updated: 2025/07/14 15:50:08 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort_aux.h"
#include "auxiliary.h"
#include "libft.h"

#include <stdlib.h>

/* Executes the operation sequence from `ops_to_exec` on stacks `a` and `b`.
 * All executed operations will be automatically added to the final list of
 * operations `full_ops_list` */
/* +++ */
void	ops_exec(t_operations *full_ops_list, t_operations *ops_to_exec,
			t_stack *a, t_stack *b)
{
	size_t	i;

	i = 0;
	while (i < ops_to_exec->size)
	{
		if (ops_to_exec->arr[i] == SA)
			stack_swap(full_ops_list, a, STACK_A);
		if (ops_to_exec->arr[i] == SB)
			stack_swap(full_ops_list, b, STACK_B);
		if (ops_to_exec->arr[i] == SS)
		{
			stack_swap(full_ops_list, a, STACK_A);
			stack_swap(full_ops_list, b, STACK_B);
		}
		if (ops_to_exec->arr[i] == PA)
			stack_push_a(full_ops_list, a, b);
		if (ops_to_exec->arr[i] == PB)
			stack_push_b(full_ops_list, a, b);
		if (ops_to_exec->arr[i] == RA)
			stack_rotate(full_ops_list, a, STACK_A);
		ops_exec_rest(full_ops_list, ops_to_exec,
			pack_args(3, (void *)a, (void *)b, (void *)&i));
		++i;
	}
}

/* +++ */
void	ops_exec_rest(t_operations *full_ops_list,
			t_operations *ops_to_exec, void **pack)
{
	t_stack	*a;
	t_stack	*b;
	size_t	i;

	a = (void *)pack[0];
	b = (void *)pack[1];
	i = *(size_t *)pack[2];
	if (ops_to_exec->arr[i] == RB)
		stack_rotate(full_ops_list, b, STACK_B);
	if (ops_to_exec->arr[i] == RR)
	{
		stack_rotate(full_ops_list, a, STACK_A);
		stack_rotate(full_ops_list, b, STACK_B);
	}
	if (ops_to_exec->arr[i] == RRA)
		stack_reverse_rotate(full_ops_list, a, STACK_A);
	if (ops_to_exec->arr[i] == RRB)
		stack_reverse_rotate(full_ops_list, b, STACK_B);
	if (ops_to_exec->arr[i] == RRR)
	{
		stack_reverse_rotate(full_ops_list, a, STACK_A);
		stack_reverse_rotate(full_ops_list, b, STACK_B);
	}
	free(pack);
}

/* Finds and returns the shortest sequence from an array of
 * operation sequences */
/* +++ */
t_operations	*find_shortest_op_seq(t_operations **ops_arr, size_t size)
{
	t_operations	*ptr;
	size_t			min_ind;
	size_t			i;

	i = 1;
	min_ind = 0;
	while (i < size)
	{
		if (ops_arr[i]->size < ops_arr[min_ind]->size)
			min_ind = i;
		++i;
	}
	ptr = ops_arr[min_ind];
	return (ptr);
}
