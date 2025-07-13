/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliary.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 12:16:53 by dchernik          #+#    #+#             */
/*   Updated: 2025/07/13 18:54:43 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "auxiliary.h"

size_t	min(const size_t num1, const size_t num2)
{
	if (num1 <= num2)
		return (num1);
	return (num2);
}

size_t	max(const size_t num1, const size_t num2)
{
	if (num1 >= num2)
		return (num1);
	return (num2);
}

/* Returns the number of digits in `num` */
int	count_digits(long long num)
{
	int	cnt;

	cnt = 0;
	if (num == 0)
		return (1);
	while (num != 0)
	{
		num /= 10;
		++cnt;
	}
	return (cnt);
}

/* Returns the digit of a number at the specified index */
int	get_digit(long long num, const int len, const int base, const int ind)
{
	int	digit;
	int	i;

	if (num < 0)
		num *= -1;
	i = len - 1;
	while (i >= ind)
	{
		digit = num % base;
		num /= base;
		--i;
	}
	return (digit);
}

/* Checks if the number is in range of [INT_MIN; INT_MAX] */
int	num_in_range(const char *num, const int left, const int right)
{
	long long	number;

	number = ft_atoll(num);
	if (number < left || number > right)
		return (0);
	return (1);
}
