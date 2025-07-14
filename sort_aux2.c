#include "sort_aux.h"
#include "auxiliary.h"
#include "libft.h"

#include <stdlib.h>

/* Returns -1 in case of an error and 0 if it's impossible sort the stack by rotating it */
/* +++ */
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
/* +++ */
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
 
/* +++ */
int	substitute_r_rr(t_operations *ops)
{
	t_ops_type	*new_arr;
	t_ops_type	*arr;
	size_t		i;

	new_arr = (t_ops_type *)malloc(ops->size * sizeof (t_ops_type));
	if (!new_arr)
		return (0);
	arr = ops->arr;
	substitute_r_rr_alg(ops, arr, new_arr);
	i = 0;
	while (i < ops->size)
	{
		ops->arr[i] = new_arr[i];
		++i;
	}
	free(new_arr);
	return (1);
}

/* +++ */
void	substitute_r_rr_alg(t_operations *ops, t_ops_type *a, t_ops_type *new_arr)
{
	size_t		i;
	size_t		new_arr_ind;

	i = 0;
	new_arr_ind = 0;
	while (i < ops->size - 1)
	{
		if ((a[i] == RA && a[i + 1] == RB) || (a[i] == RB && a[i + 1] == RA))
		{
			new_arr[new_arr_ind] = RR;
			++i;
		}
		else if ((a[i] == RRA && a[i + 1] == RRB) ||
				(a[i] == RRB && a[i + 1] == RRA))
		{
			new_arr[new_arr_ind] = RRR;
			++i;
		}
		else
			new_arr[new_arr_ind] = a[i];
		++new_arr_ind;
		++i;
	}
	new_arr[new_arr_ind] = a[i];
	ops->size = new_arr_ind + 1;
}

/* +++ */
int		substitute_s_ss(t_operations *ops)
{
	t_ops_type	*arr;
	t_ops_type	*new_arr;
	size_t		i;

	new_arr = (t_ops_type *)malloc(ops->size * sizeof (t_ops_type));
	if (!new_arr)
			return (0);
	arr = ops->arr;	
	substitute_s_ss_alg(ops, arr, new_arr);

	i = 0;
	while (i < ops->size)
	{
		arr[i] = new_arr[i];
		++i;
	}
	free(new_arr);
	return (1);
}
