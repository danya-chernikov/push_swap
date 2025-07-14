/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 12:16:50 by dchernik          #+#    #+#             */
/*   Updated: 2025/07/14 03:24:00 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#include "main_aux.h"
#include "libft.h"
#include "auxiliary.h"
#include "quick_sort.h"
#include "sorting.h"

int	main(int argc, char **argv)
{
	t_stack			a;
	t_stack			b;
	t_operations	ops;
	int				exit_code;
	int				i;

	if (argc == 1)
		exit(1);
	i = 0;
	exit_code = 0;
	while (i < 1)
	{
		int	prepare_args(t_stack *a, t_stack *b)
		{
			size_t			elems_num;
			int				f_string_arg;
			char			**nums_to_sort;
			char			**args;

			/* PARSING PART */
			f_string_arg = 0;
			nums_to_sort = NULL;
			args = NULL;

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
		}

		/* SORTING PART */
		if (sorting(&ops, &a, &b, elems_num))
			ops_print(&ops);
		else
			exit_code = 1;

	} // while (i < 1)
	if (exit_code)
		write(STDERR_FILENO, ERROR_MSG, ft_strlen(ERROR_MSG));

	/* Free all the staff */
	if (f_string_arg)
		string_args_free(nums_to_sort);
	if (ops.f_exist)
		ops_free(&ops);
	if (a.exist)
		stack_free(&a);
	if (b.exist)
		stack_free(&b);

	exit(exit_code);
}
