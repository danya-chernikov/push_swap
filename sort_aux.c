/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 12:17:28 by dchernik          #+#    #+#             */
/*   Updated: 2025/07/14 13:35:26 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort_aux.h"
#include "auxiliary.h"
#include "libft.h"

#include <stdlib.h>

/* sort_four() */

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

/* Returns -1 in case of an error and 0 if it's impossible sort the stack by rotating it */
int	rotate_stack_until_sorted(t_operations *ops, t_stack *stack, t_stack_type stype)
{
	long long	rr_ops_num;
	long long	r_ops_num;

	r_ops_num = 0;
	rr_ops_num = 0;
	r_ops_num = r_til_sorted(ops, stack);
	rr_ops_num = rr_til_sorted(ops, stack);
	if (r_ops_num == -1 || rr_ops_num == -1)
		return (-1);
	if (r_ops_num > 0 || rr_ops_num > 0)
	{
		if (r_ops_num <= rr_ops_num)
			stack_rotate_n_times(ops, stack, stype, r_ops_num);
		else
			stack_reverse_rotate_n_times(ops, stack, stype, rr_ops_num);
	}
	else if (r_ops_num == 0 && rr_ops_num == 0)
		return (0);
	return (1);
}

/* Moves the element to the top of the stack by executing either `ra` or `rra` consecutively
 * in the most efficient way. This function does change the stack. When elem_ind == 0 means
 * element is already on top */
void	move_elem_to_top(t_operations *ops, t_stack *stack, t_stack_type stype, int elem)
{
	size_t	elem_ind;

	elem_ind = stack_get_elem_index(stack, elem);
	if (elem_ind > 0) 
	{
		if (elem_ind <= stack->size / 2)
		{
			stack_rotate_n_times(ops, stack, stype, elem_ind);
		}
		else
		{
			stack_reverse_rotate_n_times(ops, stack, stype,
				stack->size - elem_ind);
		}
	}
}
 
int		substitute_r_rr(t_operations *ops)
{
	t_ops_type        *arr;
	t_ops_type        *new_arr;
	size_t          new_arr_ind;
	size_t          i;

	new_arr = (t_ops_type *)malloc(ops->size * sizeof (t_ops_type));
	if (!new_arr)
			return (0);
	i = 0;
	new_arr_ind = 0;
	arr = ops->arr;
	while (i < ops->size - 1)
	{
		if ((arr[i] == RA && arr[i + 1] == RB) || (arr[i] == RB && arr[i + 1] == RA))
		{
			new_arr[new_arr_ind] = RR;
			++i;
		}
		else if ((arr[i] == RRA && arr[i + 1] == RRB) || (arr[i] == RRB && arr[i + 1] == RRA))
		{
			new_arr[new_arr_ind] = RRR;
			++i;
		}
		else
		{
			new_arr[new_arr_ind] = arr[i];
		}
		++new_arr_ind;
		++i;
	}
	new_arr[new_arr_ind] = arr[i];
	++new_arr_ind;
	ops->size = new_arr_ind;
	i = 0;
	while (i < ops->size)
	{
		arr[i] = new_arr[i];
		++i;
	}
	free(new_arr);
	return (1);
}

int		substitute_s_ss(t_operations *ops)
{
	t_ops_type        *arr;
	t_ops_type        *new_arr;
	size_t          new_arr_ind;
	size_t          i;

	new_arr = (t_ops_type *)malloc(ops->size * sizeof (t_ops_type));
	if (!new_arr)
			return (0);
	i = 0;
	new_arr_ind = 0;
	arr = ops->arr;
	while (i < ops->size - 1)
	{
		if ((arr[i] == SA && arr[i + 1] == SB) || (arr[i] == SB && arr[i + 1] == SA))
		{
			new_arr[new_arr_ind] = SS;
			++i;
		}
		else
		{
			new_arr[new_arr_ind] = arr[i];
		}
		++new_arr_ind;
		++i;
	}
	new_arr[new_arr_ind] = arr[i];
	++new_arr_ind;
	ops->size = new_arr_ind;
	i = 0;
	while (i < ops->size)
	{
		arr[i] = new_arr[i];
		++i;
	}
	free(new_arr);
	return (1);
}

/* sort_common() */

int		sort_common_move_a_into_b(t_operations *ops, t_stack *a, t_stack *b)
{
	long long		sai;
	size_t			mov_ops_cnt;
	t_operations	**mov_ops;
	t_operations	*short_op_seq;

	while (a->size > 3)
	{
		mov_ops = alloc_mov_ops(a, b);
		if (!mov_ops)
			return (0);
		mov_ops_cnt = 0;
		sai = a->size - 1;
		while (sai >= 0)
		{
			if (!calc_mov_all_a_elems_into_b(mov_ops, a, b,
					pack_args(2, (void *)&mov_ops_cnt, (void *)&sai)))
			{
				free_mov_ops(mov_ops, a, b);
				return (0);
			}
			++mov_ops_cnt;
			--sai;
		}
		short_op_seq = find_shortest_op_seq(mov_ops, mov_ops_cnt);
		ops_exec(ops, short_op_seq, a, b);
		free_mov_ops(mov_ops, a, b);
	}
	return (1);
}

int	sort_common_move_b_into_a(t_operations *ops, t_stack *a, t_stack *b, long long sbi)
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
	return (1);
}

void	sort_common_bring_back_to_a(t_operations *ops, t_stack *a,
			t_stack *b, void **pack)
{
	int		*tmp_arr;
	int		cur_b_num;
	int		below_b_num;
	size_t	tmp_num_ind;

	tmp_arr = (int *)pack[0];
	cur_b_num = *(int *)pack[1];
	below_b_num = *(int *)pack[2];
	tmp_num_ind = array_get_elem_index(tmp_arr, a->size + 1, cur_b_num);
	if (tmp_num_ind == a->size)
	{
		stack_push_a(ops, a, b);
		stack_rotate(ops, a, STACK_A);
	}
	else
	{
		below_b_num = tmp_arr[tmp_num_ind + 1];
		move_elem_to_top(ops, a, STACK_A, below_b_num);
		stack_push_a(ops, a, b);
	}
	free(pack);
}

int		calc_mov_all_a_elems_into_b(t_operations **mov_ops, t_stack *a, t_stack *b, void **pack)
{

	int			cur_a_num;
	int			below_a_num;
	size_t		mov_ops_cnt;	
	long long	sai;

	mov_ops_cnt = *(size_t *)pack[0];
	sai = *(long long *)pack[1];
	cur_a_num = a->elems[sai];
	if (!find_elem_below(&below_a_num, cur_a_num, b))
		return (0);
	calc_mov_sai_into_b(pack_args(3, (void *)mov_ops, (void *)a, (void *)b),
		mov_ops_cnt, a->size - sai - 1, stack_get_elem_index(b, below_a_num));
	free(pack);
	return (1);
}

int		calc_mov_sai_into_b(void **pack, size_t mov_ops_cnt,
			int cur_a_num_ind, int below_a_num_ind)
{
	t_operations	tmp_ops[2];
	t_operations	**mov_ops;
	t_stack			*a;
	t_stack			*b;

	mov_ops = (t_operations **)pack[0];
	a = (t_stack *)pack[1];
	b = (t_stack *)pack[2];
	if (!ops_init(&tmp_ops[0]) || !ops_init(&tmp_ops[1]))
		return (0);
	calc_mov_top_cost_stack_a(&tmp_ops[0], a, cur_a_num_ind);
	calc_mov_top_cost_stack_b(&tmp_ops[1], b, below_a_num_ind);
	optimize_r_rr(mov_ops, &tmp_ops[0], &tmp_ops[1], mov_ops_cnt);
	ops_add(mov_ops[mov_ops_cnt], PB);
	ops_free(&tmp_ops[0]);
	ops_free(&tmp_ops[1]);
	free(pack);
	return (1);
}

t_operations	**alloc_mov_ops(t_stack *a, t_stack *b)
{
	t_operations	**mov_ops;
	size_t			i;
	size_t			j;

	mov_ops = (t_operations **)malloc((a->size + b->size) * sizeof (t_operations *));
	if (!mov_ops)
		return (NULL);
	i = 0;
	while (i < a->size + b->size)
	{
		mov_ops[i] = (t_operations *)malloc(1 * sizeof (t_operations));
		if (!mov_ops[i] || !ops_init(mov_ops[i]))
		{
			j = 0;
			while (j < i)
			{
				free(mov_ops[j]);
				mov_ops[j] = NULL;
				++j;
			}
			free(mov_ops);
			mov_ops = NULL;
			return (NULL);
		}
		++i;
	}
	return (mov_ops);
}

void	free_mov_ops(t_operations **mov_ops, t_stack *a, t_stack *b)
{
	size_t	i;

	i = 0;
	while (i < a->size + b->size)
	{
		if (mov_ops[i])
		{
			ops_free(mov_ops[i]);
			free(mov_ops[i]);
			mov_ops[i] = NULL;
		}
		++i;
	}
	free(mov_ops);
	mov_ops = NULL;
}

/* Finds find the element in stack B on top of which `cur_a_num`
 * should be placed.
 *     tmp_num_ind - Index of the number `cur_a_num` in the
 *					 temporary sorted array formed from the
 *					 elements of stack B plus `cur_a_num` */
int		find_elem_below(int *below, int num, t_stack *stack)
{
	int		*tmp_arr;
	size_t	tmp_num_ind;
	size_t	i;

	tmp_arr = (int *)malloc((stack->size + 1) * sizeof (int));
	if (!tmp_arr)
		return (0);
	i = 0;
	while(i < stack->size)
	{
		tmp_arr[i] = stack->elems[i];
		++i;
	}
	tmp_arr[i] = num;
	quick_sort(tmp_arr, 0, stack->size);
	tmp_num_ind = array_get_elem_index(tmp_arr, stack->size + 1, num);
	if (tmp_num_ind == 0)
		*below = tmp_arr[stack->size];
	else if (tmp_num_ind == stack->size)
		*below = tmp_arr[stack->size - 1];
	else
		*below = tmp_arr[tmp_num_ind - 1];
	free(tmp_arr);
	return (1);
}

/* Calculates the minimum moving cost of the element with index `cur_a_num_ind` at the top of
 * stack `a`, storing the corresponding operations in `tmp_ops_a` */
void	calc_mov_top_cost_stack_a(t_operations *tmp_ops_a, t_stack *a, size_t cur_a_num_ind)
{
	size_t	ri;
	size_t	rri;

	if (cur_a_num_ind > 0)
	{
		if (cur_a_num_ind <= a->size / 2)
		{
			ri = 0;
			while (ri < cur_a_num_ind)
			{
				ops_add(tmp_ops_a, RA);
				++ri;
			}
		}
		else
		{
			rri = 0;
			while (rri < a->size - cur_a_num_ind)
			{
				ops_add(tmp_ops_a, RRA);
				++rri;
			}
		}
	}
}

/* Calculates the minimum moving cost of the element with index `below_a_num_ind` at the top of
 * stack `b`, storing the corresponding operations in `tmp_ops_b` */
void	calc_mov_top_cost_stack_b(t_operations *tmp_ops_b, t_stack *b, size_t below_a_num_ind)
{
	size_t	ri;
	size_t	rri;

	if (below_a_num_ind > 0)
	{
		if (below_a_num_ind <= b->size / 2)
		{
			ri = 0;
			while (ri < below_a_num_ind)
			{
				ops_add(tmp_ops_b, RB);
				++ri;
			}
		}
		else
		{
			rri = 0;
			while (rri < b->size - below_a_num_ind)
			{
				ops_add(tmp_ops_b, RRB);
				++rri;
			}
		}
	}
}

void	optimize_r_rr(t_operations **mov_ops, t_operations *tmp_ops_a,
			t_operations *tmp_ops_b, size_t mov_ops_cnt)
{
	size_t	cont_ind;

	cont_ind = optimize_r_rr_part1(mov_ops, tmp_ops_a, tmp_ops_b, mov_ops_cnt);
	optimize_r_rr_part2(mov_ops, tmp_ops_a, tmp_ops_b, mov_ops_cnt, cont_ind);
}

/* Now we need to perform optimizations such as `rra` -> `rrb` => `rrr` and `ra` -> `rb` => `rr` */
size_t	optimize_r_rr_part1(t_operations **mov_ops, t_operations *tmp_ops_a,
			t_operations *tmp_ops_b, size_t mov_ops_cnt)
{
	size_t	i;

	i = 0;
	if (tmp_ops_a->size > 0 && tmp_ops_b->size > 0)
	{
		while (i < min(tmp_ops_a->size, tmp_ops_b->size))
		{
			if ((tmp_ops_a->arr[i] == RRA && tmp_ops_b->arr[i] == RRB) ||
				(tmp_ops_a->arr[i] == RRB && tmp_ops_b->arr[i] == RRA))
			{
				ops_add(mov_ops[mov_ops_cnt], RRR);
			}
			else if ((tmp_ops_a->arr[i] == RA && tmp_ops_b->arr[i] == RB) ||
					(tmp_ops_a->arr[i] == RB && tmp_ops_b->arr[i] == RA))
			{
				ops_add(mov_ops[mov_ops_cnt], RR);
			}
			else
			{
				ops_add(mov_ops[mov_ops_cnt], tmp_ops_a->arr[i]);
				ops_add(mov_ops[mov_ops_cnt], tmp_ops_b->arr[i]);
			}
			++i;
		}
	}
	return (i);
}

void	optimize_r_rr_part2(t_operations **mov_ops, t_operations *tmp_ops_a,
			t_operations *tmp_ops_b, size_t mov_ops_cnt, size_t cont_ind)
{
	if (tmp_ops_a->size < tmp_ops_b->size)
	{
		while (cont_ind < tmp_ops_b->size)
		{
			ops_add(mov_ops[mov_ops_cnt], tmp_ops_b->arr[cont_ind]);
			++cont_ind;
		}
	}
	else if (tmp_ops_a->size > tmp_ops_b->size)
	{
		while (cont_ind < tmp_ops_a->size)
		{
			ops_add(mov_ops[mov_ops_cnt], tmp_ops_a->arr[cont_ind]);
			++cont_ind;
		}
	}
}

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
