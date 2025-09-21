/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:22:52 by dchernik          #+#    #+#             */
/*   Updated: 2025/09/21 14:32:30 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "packer.h"
#include "main_aux.h"
#include "libft.h"
#include <unistd.h>

/*
 * s[0] - stack a
 * s[1] - stack b
 *
 * v[0] - exit_code
 * v[1] - elems_num
 * v[2] - f_string_arg
 * v[3] - i
 * v[4] - argc
 * 
 * c[0] = argv
 * c[1] = nums_to_sort
 * */
void	main_loop(t_operations *ops, t_stack *s, size_t *v, char ***c)
{
	char	**args;

	args = NULL;
	while (v[J] < 1)
	{
		if (!check_string_arg(&c[NUMS_TO_SORT], c[ARGV],
				v[ARGC], (int *)&v[F_STRING_ARG]))
		{
			v[EXIT_CODE] = 1;
			break ;
		}
		args = det_args_source(c[NUMS_TO_SORT], &v[ELEMS_NUM], c[ARGV],
				pack_args(2, (void *)&v[ARGC], (void *)&v[F_STRING_ARG]));
		if (!parsing(args, &s[STACK_A], &s[STACK_B],
				pack_args(2, (void *)&v[ELEMS_NUM], (void *)&v[F_STRING_ARG])))
		{
			v[EXIT_CODE] = 1;
			break ;
		}
		if (!sorting(ops, &s[STACK_A], &s[STACK_B], v[ELEMS_NUM]))
			v[EXIT_CODE] = 1;
		++v[J];
	}
	if (v[EXIT_CODE])
		write(STDERR_FILENO, ERROR_MSG, ft_strlen(ERROR_MSG));
}

void	free_all(char **nums_to_sort, t_operations *ops, t_stack *s, size_t *v)
{
	if (v[F_STRING_ARG])
		string_args_free(nums_to_sort);
	if (ops->f_exist)
		ops_free(ops);
	if (s[STACK_A].f_exist)
		stack_free(&s[STACK_A]);
	if (s[STACK_B].f_exist)
		stack_free(&s[STACK_B]);
}

/* We don't have nums_to_sort here */
int	parsing(char **args, t_stack *a, t_stack *b, void **pack)
{
	int		*arr;
	size_t	elems_num;
	int		f_string_arg;

	elems_num = *(size_t *)pack[0];
	f_string_arg = *(int *)pack[1];
	if (!check_ints_validity((int)elems_num, args))
		return (cleanup_parsing(NULL, pack, 0));
	arr = malloc(elems_num * sizeof (*arr));
	if (!arr)
		return (cleanup_parsing(NULL, pack, 0));
	array_copy_atoi(arr, args, 0, elems_num);
	quick_sort(arr, 0, elems_num - 1);
	if (!check_duplicates(arr, elems_num) || !init_stacks(a, b, arr, elems_num))
		return (cleanup_parsing(arr, pack, 0));
	args_to_stack(a, elems_num, args, f_string_arg);
	return (cleanup_parsing(arr, pack, 1));
}

int	cleanup_parsing(int *arr, void **pack, int ret)
{
	if (arr)
		free(arr);
	if (pack)
		free(pack);
	return (ret);
}

int	sorting(t_operations *ops, t_stack *a, t_stack *b, size_t elems_num)
{
	if (!stack_sorted(a))
	{
		if (!ops_init(ops))
			return (0);
		if (!launch_sort(ops, a, b, elems_num)
			|| !substitute_r_rr(ops) || !substitute_s_ss(ops))
		{
			ops_free(ops);
			return (0);
		}
		ops_print(ops);
	}
	return (1);
}
