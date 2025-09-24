/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 12:17:15 by dchernik          #+#    #+#             */
/*   Updated: 2025/09/24 15:06:41 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack_basis.h"
#include "stack_ops.h"
#include "libft.h"

#include <stdlib.h>

int	ops_init(t_operations *ops)
{
	ops->f_exist = 1;
	ops->size = 0;
	ops->capacity = OPS_LIST_INC_CHUNK_SIZE;
	ops->arr = (t_ops_type *)malloc(ops->capacity * sizeof (t_ops_type));
	if (!ops->arr)
		return (0);
	return (1);
}

void	ops_free(t_operations *ops)
{
	ops->f_exist = 0;
	ops->capacity = 0;
	ops->size = 0;
	free(ops->arr);
	ops->arr = NULL;
}

void	ops_add(t_operations *ops, const t_ops_type op)
{
	ops->arr[ops->size] = op;
	++(ops->size);
}

void	ops_print(const t_operations *ops)
{
	size_t	i;

	i = 0;
	while (i < ops->size)
	{
		print_op_by_type(ops->arr[i]);
		++i;
	}
}

void	print_op_by_type(const t_ops_type op)
{
	if (op == SA)
		ft_printf("%s\n", SA_OP_STR);
	if (op == SB)
		ft_printf("%s\n", SB_OP_STR);
	if (op == SS)
		ft_printf("%s\n", SS_OP_STR);
	if (op == PA)
		ft_printf("%s\n", PA_OP_STR);
	if (op == PB)
		ft_printf("%s\n", PB_OP_STR);
	if (op == RA)
		ft_printf("%s\n", RA_OP_STR);
	if (op == RB)
		ft_printf("%s\n", RB_OP_STR);
	if (op == RR)
		ft_printf("%s\n", RR_OP_STR);
	if (op == RRA)
		ft_printf("%s\n", RRA_OP_STR);
	if (op == RRB)
		ft_printf("%s\n", RRB_OP_STR);
	if (op == RRR)
		ft_printf("%s\n", RRR_OP_STR);
}
