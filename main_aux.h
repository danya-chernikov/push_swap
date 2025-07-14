/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_aux.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:22:56 by dchernik          #+#    #+#             */
/*   Updated: 2025/07/14 15:31:20 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(MAIN_AUX_H)
# define MAIN_AUX_H

# include "stack_basis.h"
# include "auxiliary.h"
# include "args_parser.h"
# include "sorting.h"

# include <stdlib.h>

# define ERROR_MSG	"Error\n"

int		parsing(char **args, t_stack *a, t_stack *b, void **pack);
int		sorting(t_operations *ops, t_stack *a, t_stack *b, size_t elems_num);
int		init_stacks(t_stack *a, t_stack *b, int *arr, size_t elems_num);
int		check_string_arg(char ***nums_to_sort, char **argv,
			int argc, int *f_string_arg);
char	**det_args_source(char **nums_to_sort, size_t *elems_num,
			char **argv, void **pack);
int		launch_sort(t_operations *ops, t_stack *a, t_stack *b,
			size_t elems_num);

#endif
