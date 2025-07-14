/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:23:11 by dchernik          #+#    #+#             */
/*   Updated: 2025/07/14 17:44:45 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#include "main_aux.h"
#include "libft.h"
#include "auxiliary.h"
#include "quick_sort.h"
#include "sorting.h"

int main(int argc, char **argv)
{
	t_stack a;
	t_stack b;
	t_operations ops;

	int exit_code;
	size_t elems_num;
	int f_string_arg;
	char **nums_to_sort;
	char **args;
	int	i;

	exit_code = 0;
	f_string_arg = 0;
	args = NULL;
	nums_to_sort = NULL;
	if (argc == 1)
		exit(1);
	i = 0;
	while (i < 1)
	{
		if (!check_string_arg(&nums_to_sort, argv, argc, &f_string_arg))
		{
			exit_code = 1;
			break ;	
		}
		args = det_args_source(nums_to_sort, &elems_num, argv,
			pack_args(2, (void *)&argc, (void *)&f_string_arg));
		if (!parsing(args, &a, &b,
			pack_args(2, (void *)&elems_num, (void *)&f_string_arg)))
		{
			exit_code = 1;
			break ;
		}
		if (!sorting(&ops, &a, &b, elems_num))
			exit_code = 1;
		++i;
	}
	if (exit_code)
		write(STDERR_FILENO, ERROR_MSG, ft_strlen(ERROR_MSG));
	if (f_string_arg)
			string_args_free(nums_to_sort);
	if (ops.f_exist)
		ops_free(&ops);
	stack_free(&a);
	stack_free(&b);
	return (exit_code);
}
