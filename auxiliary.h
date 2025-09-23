/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliary.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:54:52 by dchernik          #+#    #+#             */
/*   Updated: 2025/09/23 14:37:18 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(AUXILIARY_H)
# define AUXILIARY_H

/* auxiliary.c */
size_t	min(const size_t num1, const size_t num2);
size_t	max(const size_t num1, const size_t num2);
int		count_digits(long long num);
int		get_digit(long long num, const int len, const int base, const int ind);
int		is_number(const char *num);

/* auxiliary2.c */
int		num_in_range(const char *num, int left, int right);
int		array_sorted(const int *arr, const size_t size);
void	array_copy(int *arr_dst, const int *arr_src, const size_t size);
void	array_copy_atoi(int *arr_dst, char **arr_src,
			const size_t src_spos, const size_t size);
void	print_n_times(const char *str, const size_t n);

/* auxiliary3.c */
size_t	array_get_elem_index(const int *arr, const size_t size,
			const int number);

#endif
