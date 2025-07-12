/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 12:17:28 by dchernik          #+#    #+#             */
/*   Updated: 2025/07/12 17:05:32 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort_aux.h"
#include "auxiliary.h"
#include "libft.h"

#include <stdlib.h>

/* Checks whether applying a swap operation results
 * in the stack being sorted. This function does not
 * modify the stack, so we pass `NOP` as the operation
 * to perform */
int		check_swap(t_operations *ops, t_stack *stack)
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

/* Moves the element to the top of the stack by executing either `ra` or `rra` consecutively
 * in the most efficient way. This function does change the stack */
void	move_elem_to_top(t_operations *ops, t_stack *stack, stack_type stype, int elem)
{
	size_t	elem_ind;

	elem_ind = stack_get_elem_index(stack, elem);
	if (elem_ind > 0) /* elem_ind == 0 means element is already on top */
	{
		if (elem_ind <= stack->size / 2)
		{
			stack_rotate_n_times(ops, stack, stype, elem_ind);
			print_n_times("ra\n", elem_ind);
		}
		else
		{
			stack_reverse_rotate_n_times(ops, stack, stype, stack->size - elem_ind);
			print_n_times("rra\n", stack->size - elem_ind);
		}
	}
}

/* If op2 is reversed operation for op1 returns 1 */
int		ops_reciprocal(ops_type op1, ops_type op2)
{
    if ((op1 == RA && op2 == RRA) || (op1 == RRA && op2 == RA))
        return (1);
    if ((op1 == RB && op2 == RRB) || (op2 == RB && op1 == RRB))
        return (1);
    if ((op1 == RR && op2 == RRR) || (op2 == RR && op1 == RRR))
        return (1);
    return (0);
}
 
/* Removes all chains that do not make sense of the form
 * `ra`/`rb`/`rr` [1 or more] -> `rra`/`rrb`/`rrr` [1 or more].
 * Returns newly allocated array of operations without those
 * were removed. Returns NULL when encountered with an error */
int	remove_paired_r_rr(t_operations *ops)
{
    size_t      i;          /* Array counter */
	size_t		di;			/* Index of operations being deleted */
    
    ops_type    fnd_op;     /* The first operation found */
    size_t      fnd_op_cnt; /* Counts how many operations of this type were found */
    size_t      fnd_op_ind; /* Index of the first found operation */
     
    ops_type    rev_op;     /* The reversed operation of the found operation fnd_op */
    size_t      rev_op_cnt; /* Counts how many reversed operations of the fnd_op were found */
    size_t      rev_op_ind; /* Index of the first reversed operation found after the last operation of the fnd_op type */

	size_t		del_ops_cnt; /* Counter of deleted operations */
	size_t		new_arr_ind;

	size_t		new_arr_size;
	char		*ops_inds;
	ops_type	*new_arr;
	ops_type	*arr;

	ops_inds = (char *)ft_calloc(ops->size, sizeof (char));
	if (!ops_inds)
		return (0);
    
    i = 0;
    fnd_op_cnt = 0;
	rev_op_cnt = 0;
	del_ops_cnt = 0;
	arr = ops->arr;
    while (i < ops->size)
    {
        if (arr[i] == RA || arr[i] == RB || arr[i] == RR ||
				arr[i] == RRA || arr[i] == RRB || arr[i] == RRR)
        {
            fnd_op = arr[i];
            fnd_op_ind = i;
            while ((arr[i] == fnd_op) && (i < ops->size))
            {
                ++fnd_op_cnt;
                ++i;
            }
            if (i < ops->size)
            {
                if (ops_reciprocal(fnd_op, arr[i]))
                {
                    rev_op = arr[i];
                    rev_op_ind = i;
                    while (arr[i] == rev_op && i < ops->size)
                    {
                        ++rev_op_cnt;
                        ++i;
                    }
                    if (rev_op_cnt >= fnd_op_cnt)
                    {
						di = fnd_op_ind;
                        while (di < fnd_op_ind + fnd_op_cnt * 2)
                        {
							ops_inds[di] = 1;
							++del_ops_cnt;
							++di;
                        }
                        i = fnd_op_ind + fnd_op_cnt * 2;
						fnd_op_cnt = 0;
						rev_op_cnt = 0;
                        continue ;
                    }
                    else // rev_op_cnt < fnd_op_cnt
                    {
						di = fnd_op_ind + (fnd_op_cnt - rev_op_cnt);
                        while (di < rev_op_ind + rev_op_cnt)
                        {
							ops_inds[di] = 1;
							++del_ops_cnt;
							++di;
                        }
						i = rev_op_ind + rev_op_cnt;
						fnd_op_cnt = 0;
						rev_op_cnt = 0;
						continue ;
                    }
                }
                else // !ops_reciprocal(fnd_op, arr[i])
                {
                    fnd_op_cnt = 0;
                    rev_op_cnt = 0;
                    ++i;
                    continue ;
                }
            } // if (i < *size)

        } // if (arr[i] == RA || arr[i] == RB || arr[i] == RR || arr[i] == RRA || arr[i] == RRB || arr[i] == RRR)

        ++i;

    } // while (i < *size)

	/* We just created a temporary array to store all operations except those that were deleted */
	new_arr_size = ops->size - del_ops_cnt;
	new_arr = (ops_type *)malloc(new_arr_size * sizeof (ops_type));
	if (!new_arr)
	{
		free(ops_inds);
		return (0);
	}

	/* Store in this temporary array only operations that should not be deleted */
	i = 0;
	new_arr_ind = 0;
	while (i < ops->size)
	{
		if (!ops_inds[i])
		{
			new_arr[new_arr_ind] = arr[i];
			++new_arr_ind;
		}
		++i;
	}

	/* Update the original array with new values */
	ops->size = new_arr_size;
	i = 0;
	while (i < ops->size)
	{
		arr[i] = new_arr[i];
		++i;
	}

	free(new_arr);
	free(ops_inds);
	return (1);
}

/* sort_common() */


/* Executes the operation sequence from `ops_to_exec` on stacks `a` and `b`. All executed
 * operations will be automatically added to the final list of operations `full_ops_list` */
void	ops_exec(t_operations *full_ops_list, t_operations *ops_to_exec, t_stack *a, t_stack *b)
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
		++i;
	}
}

/* Finds and returns the shortest sequence from an array of operation sequences */
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
