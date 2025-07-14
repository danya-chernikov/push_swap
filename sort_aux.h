/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_aux.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 12:17:30 by dchernik          #+#    #+#             */
/*   Updated: 2025/07/14 15:05:18 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(SORT_AUX_H)
# define SORT_AUX_H

#include "stack_basis.h"
#include "stack_ops.h"
#include "quick_sort.h"

/* sort_four() */
int				sort_four_alg(t_operations *ops, t_stack *a, t_stack *b);
void			sort_four_bring_back_to_a(t_operations *ops, t_stack *a,
					t_stack *b, size_t *i);
int				check_swap(t_operations *ops, t_stack *stack);
size_t			r_til_sorted(t_operations *ops, t_stack *stack);
size_t			rr_til_sorted(t_operations *ops, t_stack *stack);
int				rotate_stack_until_sorted(t_operations *ops, t_stack *stack,
					t_stack_type stype);
void			move_elem_to_top(t_operations *ops,
				t_stack *stack, t_stack_type stype, int elem);

int				substitute_r_rr(t_operations *ops);
void			substitute_r_rr_alg(t_operations *ops,t_ops_type *a,
					t_ops_type *new_arr);
int				substitute_s_ss(t_operations *ops);
void			substitute_s_ss_alg(t_operations *ops, t_ops_type *arr,
					t_ops_type *new_arr);

/* sort_common() */
int				sort_common_move_a_into_b(t_operations *ops, t_stack *a, t_stack *b);
int				sort_common_move_b_into_a(t_operations *ops,
					t_stack *a, t_stack *b, long long sbi);
void			sort_common_bring_back_to_a(t_operations *ops, t_stack *a,
					t_stack *b, void **pack);
void			sort_common_move_a_into_b_init_vars(size_t *mov_ops_cnt,
					long long *sai, t_stack *a);
int				calc_mov_all_a_elems_into_b(t_operations **mov_ops, 
					t_stack *a, t_stack *b, void **pack);
int				calc_mov_sai_into_b(void **pack, size_t mov_ops_cnt,
					int cur_a_num_ind, int below_a_num_ind);

t_operations	**alloc_mov_ops(t_stack *a, t_stack *b);
void			free_mov_ops(t_operations **mov_ops, t_stack *a, t_stack *b);
int				find_elem_below(int *below, int num, t_stack *stack);
void			calc_mov_top_cost_stack_a(t_operations *tmp_ops_a,
					t_stack *a, size_t cur_a_num_ind);
void			calc_mov_top_cost_stack_b(t_operations *tmp_ops_b,
					t_stack *b, size_t below_a_num_ind);
void			ops_exec(t_operations *full_ops_list,
					t_operations *ops_to_exec, t_stack *a, t_stack *b);
void			ops_exec_rest(t_operations *full_ops_list,
					t_operations *ops_to_exec, void **pack);

void			optimize_r_rr(t_operations **mov_ops, t_operations *tmp_ops_a,
					t_operations *tmp_ops_b, size_t mov_ops_cnt);

size_t			optimize_r_rr_part1(t_operations **mov_ops, t_operations *tmp_ops_a,
					t_operations *tmp_ops_b, size_t mov_ops_cnt);

void			optimize_r_rr_part2(t_operations **mov_ops, t_operations *tmp_ops_a,
					t_operations *tmp_ops_b, size_t mov_ops_cnt, size_t cont_ind);

t_operations	*find_shortest_op_seq(t_operations **ops_arr, size_t size);

#endif
