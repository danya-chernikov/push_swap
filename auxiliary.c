/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliary.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 12:16:53 by dchernik          #+#    #+#             */
/*   Updated: 2025/09/23 14:37:08 by dchernik         ###   ########.fr       */
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

int	is_number(const char *num)
{
	size_t	i;

	if ((num[0] != '-') && !ft_isdigit((num[0])))
		return (0);
	if ((num[0] == '-') && (num[1] == '0'))
		return (0);
	if ((num[0] == '-') && (ft_strlen(num) == 1))
		return (0);
	if ((num[0] == '0') && (ft_strlen(num) > 1))
		return (0);
	i = 1;
	while (i < ft_strlen(num))
	{
		if (!ft_isdigit(num[i]))
			return (0);
		++i;
	}
	return (1);
}
