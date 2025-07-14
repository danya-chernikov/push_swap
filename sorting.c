/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 12:17:23 by dchernik          #+#    #+#             */
/*   Updated: 2025/07/14 12:47:58 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sorting.h"
#include "libft.h"
#include "auxiliary.h"

#include <stdlib.h>

void	sort_two(t_operations *ops, t_stack *stack)
{
	stack_swap(ops, stack, STACK_A);
}

/* Sorts the stack consiting of three arbitrary elements
 * performing minimum possible amount of operations. If
 * the stack is already sorted does nothing */
void	sort_three(t_operations *ops, t_stack *stack)
{
	int	*a;

	a = stack->elems;
	if ((a[0] < a[1]) && (a[1] > a[2]) && (a[0] < a[2]))
	{
			stack_reverse_rotate(ops, stack, STACK_A);
	}
	if ((a[0] > a[1]) && (a[1] < a[2]) && (a[0] < a[2]))
	{
		stack_rotate(ops, stack, STACK_A);
	}
	if ((a[0] < a[1]) && (a[1] > a[2]) && (a[0] > a[2]))
	{
		stack_reverse_rotate(ops, stack, STACK_A);
		stack_swap(ops, stack, STACK_A);
	}	
	if ((a[0] > a[1]) && (a[1] < a[2]) && (a[0] > a[2]))
	{
		stack_swap(ops, stack, STACK_A);
	}
	if ((a[0] < a[1]) && (a[1] < a[2]) && (a[0] < a[2]))
	{
		stack_swap(ops, stack, STACK_A);
		stack_reverse_rotate(ops, stack, STACK_A);
	}
}

/* First, we try rotating three times and reverse rotating
 * three times to see if the array gets sorted. If not, we
 * push the top element of stack A into stack B, sort stack A,
 * determine the element in A on top of which the element from
 * B should be placed, move that element to the top of A using
 * `ra` or `rra` (in the most efficient way, of course), push
 * the element from B back onto the top of A, and finally `ra`
 * or `rra` stack A until it is sorted. The `rr_ops_num` and
 * `r_ops_num` were declared as `long long` because, in addition
 * to being able to hold `size_t` values, these variables must
 * also be capable of holding -1 to signal an error */
int		sort_four(t_operations *ops, t_stack *a, t_stack *b)
{
	int		res;

	res = check_swap(ops, a);
	if (res == -1)
		return (0);
	if (res)
	{
		stack_swap(ops, a, STACK_A);
		return (1);
	}
	res = rotate_stack_until_sorted(ops, a, STACK_A);
	if (res < 0)
		return (0);
	else if (!res)
	{
		stack_push_b(ops, a, b);
		if (!stack_sorted(a))
			sort_three(ops, a);	
		if (!sort_four_alg(ops, a, b))
			return (0);
	}
	return (1);
}

/* Now let's find in stack B the nearest number NUM to
 * the a->top that is less than a->top. Then let's
 * evaluate the cost of moving a->top on top of NUM.
 *
 * If the nearest number NUM is going to be the minimum
 * or maximum number when placed in stack B, we just need
 * to place it above the current largest number in stack B.
 *
 * If NUM is neither the minimum nor the maximum, it should
 * be placed above the nearest number NUM in stack B. Let's
 * calculate the minimum number of operations needed to do
 * this. We calculate the minimum number of operations for
 * each number in stack A. Then, we choose the element with
 * the shortest operation sequence and execute it, moving
 * the element into stack A in the correct position.
 *
 * We should place `cur_a_num` on top of the next biggest
 * number in stack B, i.e., `below_a_num`. Let's find the
 * most efficient way to do this in terms of the number of
 * operations. In the general case, to place a number
 * `cur_a_num` from stack A into stack B above `below_a_num`,
 * we first need to bring both elements to the tops of their
 * respective stacks — and do so as efficiently as possible.
 * Once both elements are on top, we simply execute the `pb`
 * command, and voilà — `cur_a_num` is in the correct position.
 *
 *     i			    - Auxiliary counter;
 *
 *     sai			    - Index of stack A. Element indexing in
 *						  both stack goes from top to bottom;
 *
 *     cur_a_num	    - This is the current number from stack A
 *						  for which we are counting the minimum
 *						  number of operations required to place
 *						  it in the correct position in stack B;
 *
 *     below_a_num_ind	- The element from stack B on top of which
 *						  `cur_a_num` must be placed;
 *
 *     mov_ops			- Array of operations needed to place each
 *						  element from stack A into its correct
 *						  position in stack B. After filling in this
 *						  array, we'll simply execute the shortest
 *						  sequence of operations from it to place the
 *						  next element from stack A into stack B;
 *
 *     tmp_ops_a
 *     tmp_ops_b		- Auxiliary arrays of operations for stacks A and B.
 *						  These arrays store the operations needed to move
 *						  `cur_a_num` (for stack A) and `below_a_num` (for
 *						  stack B) to the top of their respective stacks. */
int		sort_common(t_operations *ops, t_stack *a, t_stack *b)
{
	long long	sbi;

	stack_push_b(ops, a, b);
	stack_push_b(ops, a, b);
	if (!move_a_into_b(ops, a, b))
		return (0);
	sort_three(ops, a);
	sbi = b->size - 1;
	while (sbi >= 0)
	{
		int		cur_b_num;
		int		below_b_num;
		int		*tmp_arr;
		size_t	i;

		cur_b_num = b->elems[sbi];
		tmp_arr = (int *)malloc((a->size + 1) * sizeof (int));
		if (!tmp_arr)
			return (0);
		i = 0;
		while(i < a->size)
		{
			tmp_arr[i] = a->elems[i];
			++i;
		}
		tmp_arr[i] = cur_b_num;
		quick_sort(tmp_arr, 0, a->size);
		sort_common_bring_back_to_a(ops, a, b,
			pack_args(3, (void *)tmp_arr,
				(void *)&cur_b_num,  (void *)&below_b_num));
		free(tmp_arr);
		--sbi;
	}
	if (!stack_sorted(a))
		if (rotate_stack_until_sorted(ops, a, STACK_A) < 0)
			return (0);
	return (1);
}
