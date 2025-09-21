/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_aux.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:22:56 by dchernik          #+#    #+#             */
/*   Updated: 2025/09/21 14:01:16 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(MAIN_AUX_H)
# define MAIN_AUX_H

# include "stack_basis.h"
# include "auxiliary.h"
# include "args_parser.h"
# include "sorting.h"

# include <stdlib.h>

# define ERROR_MSG		"Error\n"
# define STACK_A		0
# define STACK_B		1
# define EXIT_CODE		0
# define ELEMS_NUM		1
# define F_STRING_ARG	2
# define J				3
# define ARGC			4
# define ARGV			0
# define NUMS_TO_SORT	1
/*
 * s[0] - stack a
 * s[1] - stack b
 *
 * v[0] - exit_code
 * v[1] - elems_num
 * v[2] - f_string_arg
 * v[3] - j
 * v[4] - argc
 * 
 * c[0] = argv
 * c[1] = nums_to_sort
 * */

/* main_aux.c */
void	main_loop(t_operations *ops, t_stack *s, size_t *v, char ***c);
void	free_all(char **nums_to_sort, t_operations *ops, t_stack *s, size_t *v);
int		parsing(char **args, t_stack *a, t_stack *b, void **pack);
int		cleanup_parsing(int *arr, void **pack, int ret);
int		sorting(t_operations *ops, t_stack *a, t_stack *b, size_t elems_num);

/* main_aux2.c */
int		init_stacks(t_stack *a, t_stack *b, int *arr, size_t elems_num);
int		check_string_arg(char ***nums_to_sort, char **argv,
			int argc, int *f_string_arg);
char	**det_args_source(char **nums_to_sort, size_t *elems_num,
			char **argv, void **pack);
int		launch_sort(t_operations *ops, t_stack *a, t_stack *b,
			size_t elems_num);

#endif
