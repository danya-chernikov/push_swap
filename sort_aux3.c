/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_aux3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:24:02 by dchernik          #+#    #+#             */
/*   Updated: 2025/07/14 15:24:03 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort_aux.h"
#include "auxiliary.h"
#include "libft.h"

#include <stdlib.h>

/* +++ */
void	substitute_s_ss_alg(t_operations *ops, t_ops_type *arr, t_ops_type *new_arr)
{
	size_t	i;
	size_t	new_arr_ind;

	i = 0;
	new_arr_ind = 0;
	while (i < ops->size - 1)
	{
		if ((arr[i] == SA && arr[i + 1] == SB) ||
				(arr[i] == SB && arr[i + 1] == SA))
		{
			new_arr[new_arr_ind] = SS;
			++i;
		}
		else
			new_arr[new_arr_ind] = arr[i];
		++new_arr_ind;
		++i;
	}
	new_arr[new_arr_ind] = arr[i];
	ops->size = new_arr_ind + 1;
}

/* sort_common() */

/* +++ */
int		sort_common_move_a_into_b(t_operations *ops, t_stack *a, t_stack *b)
{
	t_operations	**mov_ops;
	size_t			mov_ops_cnt;
	long long		sai;

	while (a->size > 3)
	{
		mov_ops = alloc_mov_ops(a, b);
		if (!mov_ops)
			return (0);
		sort_common_move_a_into_b_init_vars(&mov_ops_cnt, &sai, a);
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
		ops_exec(ops, find_shortest_op_seq(mov_ops, mov_ops_cnt), a, b);
		free_mov_ops(mov_ops, a, b);
	}
	return (1);
}

/* +++ */
void	sort_common_move_a_into_b_init_vars(size_t *mov_ops_cnt,
			long long *sai, t_stack *a)
{
	*mov_ops_cnt = 0;
	*sai = a->size - 1;
}

/* +++ */
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

/* +++ */
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
