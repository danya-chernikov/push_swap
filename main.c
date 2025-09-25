/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:23:11 by dchernik          #+#    #+#             */
/*   Updated: 2025/09/25 20:15:57 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#include "main_aux.h"
#include "libft.h"
#include "auxiliary.h"
#include "quick_sort.h"
#include "sorting.h"

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
int	main(int argc, char **argv)
{
	t_stack			s[2];
	size_t			v[5];
	char			**c[2];
	t_operations	ops;

	ft_memset(v, '\0', sizeof (v));
	s[STACK_A].f_exist = 0;
	s[STACK_B].f_exist = 0;
	v[ARGC] = (size_t)argc;
	c[ARGV] = argv;
	c[NUMS_TO_SORT] = NULL;
	ops.f_exist = 0;
	if (argc == 1)
		exit(1);
	main_loop(&ops, s, v, c);
	free_all(c[NUMS_TO_SORT], &ops, s, v);
	return (v[EXIT_CODE]);
}
