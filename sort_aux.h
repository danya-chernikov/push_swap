/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_aux.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 12:17:30 by dchernik          #+#    #+#             */
/*   Updated: 2025/07/12 14:43:25 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(SORT_AUX_H)
# define SORT_AUX_H

#include "stack_basis.h"
#include "stack_ops.h"

int				check_swap(t_operations *ops, t_stack *stack);
size_t			r_til_sorted(t_operations *ops, t_stack *stack);
size_t			rr_til_sorted(t_operations *ops, t_stack *stack);

void			move_elem_to_top(t_operations *ops,
				t_stack *stack, stack_type stype, int elem);

int				ops_reciprocal(ops_type op1, ops_type op2);
int				remove_paired_r_rr(t_operations *ops);

/* sort_common() */
void			ops_exec(t_operations *full_ops_list, t_operations *ops_to_exec, t_stack *a, t_stack *b);
t_operations	*find_shortest_op_seq(t_operations **ops_arr, size_t size);

#endif
