/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 12:17:23 by dchernik          #+#    #+#             */
/*   Updated: 2025/07/13 00:52:53 by dchernik         ###   ########.fr       */
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
	// | 2 10 5 <-top
	if (stack->elems[0] < stack->elems[1] &&
		stack->elems[1] > stack->elems[2] &&
		stack->elems[0] < stack->elems[2])
	{
		stack_reverse_rotate(ops, stack, STACK_A);
		ft_printf("rra\n");
	}

	// | 5 2 10
	if (stack->elems[0] > stack->elems[1] &&
		stack->elems[1] < stack->elems[2] &&
		stack->elems[0] < stack->elems[2])
	{
		stack_rotate(ops, stack, STACK_A);
		ft_printf("ra\n");
	}

	// | 5 10 2
	// also we could just `sa -> ra` here
	// and in this case when sorting four elements
	// we can acheive better optimization by
	// removing rotating operations (see case 14
	// on the paper)
	if (stack->elems[0] < stack->elems[1] &&
		stack->elems[1] > stack->elems[2] &&
		stack->elems[0] > stack->elems[2])
	{
		stack_reverse_rotate(ops, stack, STACK_A);
		stack_swap(ops, stack, STACK_A);
		ft_printf("rra\n");
		ft_printf("sa\n");
	}
	
	// | 10 2 5
	if (stack->elems[0] > stack->elems[1] &&
		stack->elems[1] < stack->elems[2] &&
		stack->elems[0] > stack->elems[2])
	{
		stack_swap(ops, stack, STACK_A);
		ft_printf("sa\n");
	}

	// | 2 5 10	worst case
	if (stack->elems[0] < stack->elems[1] &&
		stack->elems[1] < stack->elems[2] &&
		stack->elems[0] < stack->elems[2])
	{
		stack_swap(ops, stack, STACK_A);
		stack_reverse_rotate(ops, stack, STACK_A);
		ft_printf("sa\n");
		ft_printf("rra\n");
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
	long long	rr_ops_num;
	long long	r_ops_num;
	int			swap_res;

	swap_res = check_swap(ops, a);
	if (swap_res == -1)
		return (0);
	if (swap_res)
	{
		ft_printf("sa\n");
		stack_swap(ops, a, STACK_A);
		return (1);
	}

	r_ops_num = 0;
	rr_ops_num = 0;
	r_ops_num = r_til_sorted(ops, a);
	rr_ops_num = rr_til_sorted(ops, a);
	if (r_ops_num == -1 || rr_ops_num == -1)
		return (0);

	if (r_ops_num > 0 || rr_ops_num > 0)
	{
		if (r_ops_num <= rr_ops_num)
		{
			stack_rotate_n_times(ops, a, STACK_A, r_ops_num);
			print_n_times("ra\n", r_ops_num);
		}
		else
		{
			stack_reverse_rotate_n_times(ops, a, STACK_A, rr_ops_num);
			print_n_times("rra\n", rr_ops_num);
		}
	}
	else if (r_ops_num == 0 && rr_ops_num == 0)
	{
		ft_printf("pb\n");
		stack_push_b(ops, a, b);

		if (!stack_sorted(a))
			sort_three(ops, a);
		
		size_t i = 0;
		while (i < a->capacity)
		{
			if (a->sorted[i] == *b->top)
			{
				if (i == a->capacity - 1)
				{
					ft_printf("pa\n");
					stack_push_a(ops, a, b);

					ft_printf("ra\n");
					stack_rotate(ops, a, STACK_A);
				}
				else
				{
					++i;
					while ((!stack_contains(a, a->sorted[i])) && (i < a->capacity))
						++i;

					if (i < a->capacity)
					{
						int	bottom_elem;

						bottom_elem = a->sorted[i];
						move_elem_to_top(ops, a, STACK_A, bottom_elem);

						ft_printf("pa\n");
						stack_push_a(ops, a, b);
					}
					else
					{
						ft_printf("pa\n");
						stack_push_a(ops, a, b);

						ft_printf("ra\n");
						stack_rotate(ops, a, STACK_A);
					}
				}

				if (!stack_sorted(a))
				{
					r_ops_num = 0;
					rr_ops_num = 0;
					r_ops_num = r_til_sorted(ops, a);
					rr_ops_num = rr_til_sorted(ops, a);
					if (r_ops_num == -1 || rr_ops_num == -1)
						return (0);
					if (r_ops_num > 0 || rr_ops_num > 0)
					{
						if (r_ops_num <= rr_ops_num)
						{
							stack_rotate_n_times(ops, a, STACK_A, r_ops_num);
							print_n_times("ra\n", r_ops_num);
						}
						else
						{
							stack_reverse_rotate_n_times(ops, a, STACK_A, rr_ops_num);
							print_n_times("rra\n", rr_ops_num);
						}
					}
				}

				break ;

			} // if (a->sorted[i] == *b->top)

			++i;

		} // while (i < a->capacity)

	} // else if (r_ops_num == 0 && rr_ops_num == 0)

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
 *						  stack B) to the top of their respective stacks;
 * */
int		sort_common(t_operations *ops, t_stack *a, t_stack *b)
{
	stack_push_b(ops, a, b);
	stack_push_b(ops, a, b);

	if (!move_a_into_b(ops, a, b))
		return (0);

	sort_three(ops, a);

	ft_printf("\nFINAL:\n");

	/* Let's print our stacks */
	ft_printf("\n");
	ft_printf("a | ");
	stack_print(a);
	ft_printf("b | ");
	stack_print(b);
	ft_printf("\n");

	return (1);
}

/*
		ft_printf("\n");
		ft_printf("a | ");
		stack_print(a);
		ft_printf("b | ");
		stack_print(b);
		ft_printf("\n");

		ft_printf("\nmov_ops:\n");
		i = 0;
		while (i < mov_ops_cnt)
		{
			ft_printf("%d:\n", a->elems[a->size - i - 1]);
			ops_print(mov_ops[i]);
			ft_printf("\n");
			++i;
		}
		ft_printf("\n");

		ft_printf("\nWE EXECUTE:\n");
		ops_print(short_op_seq);
		ft_printf("\n");
 */
