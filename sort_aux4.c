/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_aux4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:24:08 by dchernik          #+#    #+#             */
/*   Updated: 2025/07/14 15:24:09 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort_aux.h"
#include "auxiliary.h"
#include "libft.h"

#include <stdlib.h>

/* +++ */
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

/* +++ */
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

/* +++ */
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
				++j;
			}
			free(mov_ops);
			return (NULL);
		}
		++i;
	}
	return (mov_ops);
}

/* +++ */
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
/* +++ */
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
