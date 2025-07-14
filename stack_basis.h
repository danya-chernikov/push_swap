/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_basis.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:55:34 by dchernik          #+#    #+#             */
/*   Updated: 2025/07/14 02:52:05 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(STACK_BASIS_H)
# define STACK_BASIS_H

# include <stddef.h>

/*  [0]   [1]   [2]   [3]   [4]   [5]  <-- array indexes
 * [150] [355] [-42] [ 0 ] [124] [813] <-- elements
 *   | 							   |
 *	 v							   v
 * bottom						  top */
typedef struct s_stack
{
	int		f_exist;
	int		*elems;
	int		*sorted;
	int		*top;
	size_t	size;
	size_t	capacity;
}	t_stack;

/* stack_basis.c */
int			stack_init(t_stack *stack, const size_t capacity);
void		stack_free(t_stack *stack);
void		stack_print(t_stack *stack);
void		stack_push(t_stack *stack, const int elem);
int			*stack_pop(t_stack *stack);

/* stack_basis2.c */
int			stack_empty(t_stack *stack);
int			stack_sorted(t_stack *stack);
int			stack_contains(t_stack *stack, int elem);
int			stack_copy(t_stack *dst, t_stack *src);
long long	stack_get_elem_index(t_stack *stack, int elem);

#endif
