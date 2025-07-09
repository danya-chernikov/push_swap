#include "sorting.h"
#include "sort_aux.h"
#include "libft.h"
#include "stack_ops.h"
#include "auxiliary.h"

void	sort_two(t_stack *stack)
{
	stack_swap(stack);
}

/* Sorts the stack consiting of
 * three arbitrary elements
 * performing minimum possible
 * amount of operations. If the
 * stack is already sorted does
 * nothing */
void	sort_three(t_stack *stack)
{
	// | 2 10 5 <-top
	if (stack->elems[0] < stack->elems[1] &&
		stack->elems[1] > stack->elems[2] &&
		stack->elems[0] < stack->elems[2])
	{
		stack_reverse_rotate(stack);
		ft_printf("rra\n");
	}

	// | 5 2 10
	if (stack->elems[0] > stack->elems[1] &&
		stack->elems[1] < stack->elems[2] &&
		stack->elems[0] < stack->elems[2])
	{
		stack_rotate(stack);
		ft_printf("ra\n");
	}

	// | 5 10 2
	if (stack->elems[0] < stack->elems[1] &&
		stack->elems[1] > stack->elems[2] &&
		stack->elems[0] > stack->elems[2])
	{
		stack_reverse_rotate(stack);
		stack_swap(stack);
		ft_printf("rra\n");
		ft_printf("sa\n");
	}
	
	// | 10 2 5
	if (stack->elems[0] > stack->elems[1] &&
		stack->elems[1] < stack->elems[2] &&
		stack->elems[0] > stack->elems[2])
	{
		stack_swap(stack);
		ft_printf("sa\n");
	}

	// | 2 5 10	worst case
	if (stack->elems[0] < stack->elems[1] &&
		stack->elems[1] < stack->elems[2] &&
		stack->elems[0] < stack->elems[2])
	{
		stack_swap(stack);
		stack_reverse_rotate(stack);
		ft_printf("sa\n");
		ft_printf("rra\n");
	}
}

/* First, we try rotating three times and
 * reverse rotating three times to see if
 * the array gets sorted. If not, we push
 * the top element of stack A into stack B,
 * sort stack A, determine the element in A
 * on top of which the element from B should
 * be placed, move that element to the top
 * of A using ra or rra (in the most efficient
 * way, of course), push the element from B
 * back onto the top of A, and finally ra or
 * rra stack A until it is sorted */
int	sort_four(t_stack *a, t_stack *b)
{
	int	swap_res;
	int	r_ops_num;
	int	rr_ops_num;

	swap_res = check_swap(a);
	if (swap_res == -1)
		return (0);
	if (swap_res)
	{
		ft_printf("sa\n");
		stack_swap(a);
	}

	r_ops_num = 0;
	rr_ops_num = 0;
	r_ops_num = r_til_sorted(a);
	rr_ops_num = rr_til_sorted(a);
	if (r_ops_num == -1 || rr_ops_num == -1)
		return (0);

	if (r_ops_num > 0 || rr_ops_num > 0)
	{
		if (r_ops_num <= rr_ops_num)
		{
			stack_rotate_n_times(a, r_ops_num);
			print_n_times("ra\n", r_ops_num);
		}
		else
		{
			stack_reverse_rotate_n_times(a, rr_ops_num);
			print_n_times("rra\n", rr_ops_num);
		}
	}
	else if (r_ops_num == 0 && rr_ops_num == 0)
	{
		ft_printf("pb\n");
		stack_push_b(a, b);

		if (!stack_sorted(a))
			sort_three(a);
		
		size_t i = 0;
		while (i < a->capacity)
		{
			if (a->sorted[i] == *b->top)
			{
				if (i == a->capacity - 1)
				{
					ft_printf("pa\n");
					stack_push_a(a, b);

					ft_printf("rra\n");
					stack_reverse_rotate(a);
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
						move_elem_to_top(a, bottom_elem);

						ft_printf("pa\n");
						stack_push_a(a, b);
					}
					else
					{
						ft_printf("pa\n");
						stack_push_a(a, b);

						ft_printf("rra\n");
						stack_reverse_rotate(a);
					}
				}

				if (!stack_sorted(a))
				{
					r_ops_num = 0;
					rr_ops_num = 0;
					r_ops_num = r_til_sorted(a);
					rr_ops_num = rr_til_sorted(a);
					if (r_ops_num == -1 || rr_ops_num == -1)
						return (0);
					if (r_ops_num > 0 || rr_ops_num > 0)
					{
						if (r_ops_num <= rr_ops_num)
						{
							stack_rotate_n_times(a, r_ops_num);
							print_n_times("ra\n", r_ops_num);
						}
						else
						{
							stack_reverse_rotate_n_times(a, rr_ops_num);
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

int	sort_common(t_stack *a, t_stack *b)
{
	(void)a;
	(void)b;

	return (1);
}
