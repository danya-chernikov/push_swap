/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 12:17:23 by dchernik          #+#    #+#             */
/*   Updated: 2025/07/12 15:00:44 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sorting.h"
#include "libft.h"
#include "auxiliary.h"
#include "quick_sort.h"

#include <stdlib.h>

void	sort_two(t_operations *ops, t_stack *stack)
{
	stack_swap(ops, stack, STACK_A);
}

/* Sorts the stack consiting of
 * three arbitrary elements
 * performing minimum possible
 * amount of operations. If the
 * stack is already sorted does
 * nothing */
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

int		sort_common(t_operations *ops, t_stack *a, t_stack *b)
{
	/* First push two elements on top of stack B */
	stack_push_b(ops, a, b);
	stack_push_b(ops, a, b);

	/* Now let's find in stack B the nearest number NUM to
	 * the a->top that is less than a->top. Then let's
	 * evaluate the cost of moving a->top on top of NUM */

	/* If the nearest number NUM is going to be the minimum
	 * or maximum number when placed in stack B, we just need
	 * to place it above the current largest number in stack B */
		
	/* If NUM is neither the minimum nor the maximum, it should
	 * be placed above the nearest number NUM in stack B. Let's
	 * calculate the minimum number of operations needed to do
	 * this. We calculate the minimum number of operations for
	 * each number in stack A. Then, we choose the element with
	 * the shortest operation sequence and execute it, moving
	 * the element into stack A in the correct position */


	size_t			i; /* Auxiliary counter */

	long long		sai; /* Index of stack A */

	/* This is the current number from stack A
	 * for which we are counting the minimum
	 * number of operations required to place
	 * it in the correct position in stack B */
	int				cur_a_num;
	size_t			cur_a_num_ind;

	int				big_b_num;
	size_t			big_b_num_ind;

	/* Index of the number `cur_a_num`
	 * in the temporary sorted array
	 * formed from the elements of
	 * stack B plus `cur_a_num` */
	size_t			tmp_a_num_ind;

	int				*tmp_arr;

	/* Array of operations needed to place
	 * each element from stack A into its
	 * correct position in stack B. After
	 * filling in this array, we'll simply
	 * execute the shortest sequence of
	 * operations from it to place the next
	 * element from stack A into stack B */
	t_operations	**mov_ops;
	t_operations	tmp_ops_a;
	t_operations	tmp_ops_b;
	t_operations	*short_op_seq;
	int				mov_ops_cnt;

	mov_ops = (t_operations **)malloc((a->size + b->size) * sizeof (t_operations *));
	if (!mov_ops)
		return (0);
	i = 0;
	while (i < a->size + b->size)
	{
		mov_ops[i] = (t_operations *)malloc(1 * sizeof (t_operations));
		if (!mov_ops[i])
			return (0);
		ops_init(mov_ops[i]);
		++i;
	}

	sai = a->size - 1; // Top stack index
	/* Going from top to bottom */
	/* ELEMENT INDEXING IN BOTH STACK ALSO GOES FROM TOP TO BOTTOM */
	while (sai >= 0)
	{
		cur_a_num = a->elems[sai];
		ft_printf("Working with: %d\n", cur_a_num);

		/* Let's determine whether `cur_a_num` will be the
		 * minimum, maximum or somewhere in the middle number
		 * if placed in stack B. To do this, let's create a
		 * temporary array from the values of stack B, add
		 * `cur_a_num` to it, and sort this array */
		tmp_arr = (int *)malloc((b->size + 1) * sizeof (int));
		if (!tmp_arr)
			return (0);


		/* Copy elements from stack B into the temporary array */
		i = 0;
		while(i < b->size)
		{
			tmp_arr[i] = b->elems[i];
			++i;
		}
		tmp_arr[i] = cur_a_num;

		/* Sorting elements */
		quick_sort(tmp_arr, 0, b->size);

		ft_printf("Sorted stack B: ");
		for (size_t i = 0; i < b->size + 1; ++i)
			ft_printf("%d ", tmp_arr[i]);
		ft_printf("\n");


		tmp_a_num_ind = array_get_elem_index(tmp_arr, b->size + 1, cur_a_num);

		/* Let's find the element in stack B on top of which `cur_a_num` should be placed */
		if (tmp_a_num_ind == 0) // The smallest number in stack B
		{
			big_b_num = tmp_arr[b->size];
		}
		else if (tmp_a_num_ind == b->size) // The biggest
		{
			big_b_num = tmp_arr[b->size - 1];
		}
		else // Somewhere in the middle
		{
			big_b_num = tmp_arr[tmp_a_num_ind - 1]; // We just need to take the nearest number to `cur_a_num` in stack B that is smaller than it
		}
		ft_printf("We should place %d from A above %d in B\n", cur_a_num, big_b_num);


		// Let's determine the current index of `cur_a_num` in stack A
		cur_a_num_ind = a->size - sai - 1;
		// Let's determine the current index of `big_b_num` in stack B
		big_b_num_ind = stack_get_elem_index(b, big_b_num);

		ft_printf("Index of %d is %d\n", cur_a_num, cur_a_num_ind);
		ft_printf("Index of %d is %u\n", big_b_num, big_b_num_ind);

		/* We should place `cur_a_num` on top of the next biggest number in stack B,
		 * i.e., `big_b_num`. Let's find the most efficient way to do this in terms
		 * of the number of operations. In the general case, to place a number
		 * `cur_a_num` from stack A into stack B above `big_b_num`, we first need
		 * to bring both elements to the tops of their respective stacks — and do so
		 * as efficiently as possible. Once both elements are on top, we simply
		 * execute the `pb` command, and voilà — `cur_a_num` is in the correct position */


		ops_init(&tmp_ops_a);
		ops_init(&tmp_ops_b);

		/* If `cur_a_num` or `big_b_num` are already on top of their stacks do nothing */

		if (cur_a_num_ind > 0) // The `cur_a_num` is not on top of stack A
		{
			if (cur_a_num_ind <= a->size / 2)
			{
				for (size_t ri = 0; ri < cur_a_num_ind; ++ri)
					ops_add(&tmp_ops_a, RA);
			}
			else
			{
				for (size_t rri = 0; rri < a->size - cur_a_num_ind; ++rri)
					ops_add(&tmp_ops_a, RRA);
			}
		}
		if (big_b_num_ind > 0) // The `big_b_num` is not on top of stack B
		{
			if (big_b_num_ind <= b->size / 2)
			{
				for (size_t ri = 0; ri < big_b_num_ind; ++ri)
					ops_add(&tmp_ops_b, RB);
			}
			else
			{
				for (size_t rri = 0; rri < b->size - big_b_num_ind; ++rri)
					ops_add(&tmp_ops_b, RRB);
			}
		}

		ft_printf("tmp_ops_a:\n");
		ops_print(&tmp_ops_a);
		ft_printf("\n\n");
		ft_printf("tmp_ops_b:\n");
		ops_print(&tmp_ops_b);
		ft_printf("\n\n");

		/* Now we need to perform optimizations such as `rra` -> `rrb` => `rrr` and `ra` -> `rb` => `rr` */
		i = 0;		
		while (i < min(tmp_ops_a.size, tmp_ops_b.size))
		{
			if ((tmp_ops_a.arr[i] == RRA && tmp_ops_b.arr[i] == RRB) ||
				(tmp_ops_a.arr[i] == RRB && tmp_ops_b.arr[i] == RRA))
			{
				ops_add(mov_ops[mov_ops_cnt], RRR);
			}
			else if ((tmp_ops_a.arr[i] == RA && tmp_ops_b.arr[i] == RB) ||
					(tmp_ops_a.arr[i] == RB && tmp_ops_b.arr[i] == RA))
			{
				ops_add(mov_ops[mov_ops_cnt], RR);
			}
			else
			{
				ops_add(mov_ops[mov_ops_cnt], tmp_ops_a.arr[i]);
				ops_add(mov_ops[mov_ops_cnt], tmp_ops_b.arr[i]);
			}
			++i;
		}

		size_t	j;

		if (tmp_ops_a.size < tmp_ops_b.size)
		{
			j = i;
			while (j < tmp_ops_b.size)
			{
				ops_add(mov_ops[mov_ops_cnt], tmp_ops_b.arr[j]);
				++j;
			}
		}
		else if (tmp_ops_a.size > tmp_ops_b.size)
		{
			j = i;
			while (j < tmp_ops_a.size)
			{
				ops_add(mov_ops[mov_ops_cnt], tmp_ops_a.arr[j]);
				++j;
			}
		}

		/* And in the end we add `pb` */
		ops_add(mov_ops[mov_ops_cnt], PB);

		ft_printf("Operations for [%d] element in A to push it in B:\n", cur_a_num_ind);
		ops_print(mov_ops[mov_ops_cnt]);
		ft_printf("\n\n");


		ops_free(&tmp_ops_a);
		ops_free(&tmp_ops_b);

		free(tmp_arr);
		tmp_arr = NULL;

		++mov_ops_cnt;

		--sai;
	} // while (sai >= 0)

	/* Now we have to choose the shortest sequence of operations from mov_ops[] and execute it */
	ft_printf("Let's execute the shortest sequence of operations\n");
	short_op_seq = find_shortest_op_seq(mov_ops, mov_ops_cnt);
	ops_exec(ops, short_op_seq, a, b);

	/* Let's print our stacks */

	i = 0;
	while (i < a->size + b->size)
	{
		ops_free(mov_ops[i]);
		free(mov_ops[i]);
		++i;
	}
	free(mov_ops);
	mov_ops = NULL;

	return (1);
}
