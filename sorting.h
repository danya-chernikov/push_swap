/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 12:17:26 by dchernik          #+#    #+#             */
/*   Updated: 2025/07/14 15:47:04 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(SORTING_H)
# define SORTING_H

# include "stack_basis.h"
# include "sort_aux.h"
# include "stack_ops.h"

void	sort_two(t_operations *ops, t_stack *stack);
void	sort_three(t_operations *ops, t_stack *stack);
int		sort_four(t_operations *ops, t_stack *a, t_stack *b);
int		sort_common(t_operations *ops, t_stack *a, t_stack *b);

#endif
