#include "sort_aux.h"
#include "auxiliary.h"
#include "libft.h"

#include <stdlib.h>

/* Calculates the minimum moving cost of the element with index `cur_a_num_ind` at the top of
 * stack `a`, storing the corresponding operations in `tmp_ops_a` */
/* +++ */
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
/* +++ */
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

/* +++ */
void	optimize_r_rr(t_operations **mov_ops, t_operations *tmp_ops_a,
			t_operations *tmp_ops_b, size_t mov_ops_cnt)
{
	size_t	cont_ind;

	cont_ind = optimize_r_rr_part1(mov_ops, tmp_ops_a, tmp_ops_b, mov_ops_cnt);
	optimize_r_rr_part2(mov_ops, tmp_ops_a, tmp_ops_b, mov_ops_cnt, cont_ind);
}

/* Now we need to perform optimizations such as `rra` -> `rrb` => `rrr` and `ra` -> `rb` => `rr` */
/* +++ */
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
				ops_add(mov_ops[mov_ops_cnt], RRR);
			else if ((tmp_ops_a->arr[i] == RA && tmp_ops_b->arr[i] == RB) ||
					(tmp_ops_a->arr[i] == RB && tmp_ops_b->arr[i] == RA))
				ops_add(mov_ops[mov_ops_cnt], RR);
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

/* +++ */
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
