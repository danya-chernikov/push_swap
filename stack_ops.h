/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_ops.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 12:17:20 by dchernik          #+#    #+#             */
/*   Updated: 2025/09/22 20:03:07 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(STACK_OPS_H)
# define STACK_OPS_H

# include "stack_basis.h"

/* This is the number that will be added
 * to each newly allocated memory size
 * for the list of operations when there
 * is not enough memory to accommodate
 * new operations. In other words, it is
 * the amount by which the size of the
 * `ops_list` array will be increased during
 * each subsequent memory reallocation */
# define OPS_LIST_INC_CHUNK_SIZE	100000
# define SA_OP_STR					"sa"
# define SB_OP_STR					"sb"
# define SS_OP_STR					"ss"
# define PA_OP_STR					"pa"
# define PB_OP_STR					"pb"
# define RA_OP_STR					"ra"
# define RB_OP_STR					"rb"
# define RR_OP_STR					"rr"
# define RRA_OP_STR					"rra"
# define RRB_OP_STR					"rrb"
# define RRR_OP_STR					"rrr"

typedef enum operation_type
{
	SA,
	SB,
	SS,
	PA,
	PB,
	RA,
	RB,
	RR,
	RRA,
	RRB,
	RRR
}	t_ops_type;

/* NOP means "no operation" */
typedef enum stack_type
{
	STACK_A,
	STACK_B,
	NOP
}	t_stack_type;

typedef struct s_operations
{
	int			f_exist;
	size_t		capacity;
	size_t		size;
	t_ops_type	*arr;
}	t_operations;

/* stack_ops.c */
int		ops_init(t_operations *ops);
void	ops_free(t_operations *ops);
void	ops_add(t_operations *ops, const t_ops_type op);
void	ops_print(const t_operations *ops);
void	print_op_by_type(const t_ops_type op);

/* Operations from task's announcement */
/* stack_ops2.c */
void	stack_swap(t_operations *ops, t_stack *stack, const t_stack_type stype);
void	stack_rotate(t_operations *ops, t_stack *stack,
			const t_stack_type stype);

void	stack_reverse_rotate(t_operations *ops, t_stack *stack,
			const t_stack_type stype);

void	stack_push_a(t_operations *ops, t_stack *a, t_stack *b);
void	stack_push_b(t_operations *ops, t_stack *a, t_stack *b);

/* stack_ops3.c */
void	stack_rotate_n_times(t_operations *ops,
			t_stack *stack, const t_stack_type stype,
			const size_t n);

void	stack_reverse_rotate_n_times(t_operations *ops,
			t_stack *stack, const t_stack_type stype,
			const size_t n);

#endif
