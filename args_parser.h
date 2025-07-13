/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parser.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 12:17:34 by dchernik          #+#    #+#             */
/*   Updated: 2025/07/13 16:00:44 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(ARGS_PARSER_H)
# define ARGS_PARSER_H

/* We assume the user's architecture
 * type. When int is 64-bit, INT_MIN
 * will be -9223372036854775808, which
 * requires 20 characters to represent.
 * Therefore, 21 characters should be
 * sufficient for most non-exotic cases */
#define MAX_INT_STR_LEN	21

/* This is the number that will be added
 * to each newly allocated memory size
 * for the arguments passed via argv[1]
 * in form of a string when there
 * is not enough memory to accommodate
 * new arguments (elements to sort). In
 * other words, it is the amount by which
 * the size of the `nums_to_sort` array
 * will be increased during each subsequent
 * memory reallocation */
#define ARGS_INC_CHUNK_SIZE	8192

#include "stack_basis.h"

int		check_ints_validity(int argc, char **argv);
int		is_number(const char *num);
int		check_duplicates(const int *arr, const size_t size);
void	args_to_stack(t_stack *stack, size_t elems_num, char **argv, int f_string_arg);
size_t	get_str_args_size(char **args);
char	**split_string_arg(char **argv);
void	string_args_free(char **str_args);

#endif
