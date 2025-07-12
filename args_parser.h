/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parser.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 12:17:34 by dchernik          #+#    #+#             */
/*   Updated: 2025/07/12 12:17:35 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(ARGS_PARSER_H)
# define ARGS_PARSER_H

#include "stack_basis.h"

int		check_ints_validity(int argc, char **argv);
int		is_number(const char *num);
int		check_duplicates(const int *arr, const size_t size);
void	args_to_stack(t_stack *stack, int argc, char **argv);

#endif
