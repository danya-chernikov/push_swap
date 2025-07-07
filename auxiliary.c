#include "libft.h"
#include "auxiliary.h"

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

/* Checks if the number is in range of
 * [INT_MIN; INT_MAX] */
int	is_num_in_range(const char *num, const int left, const int right)
{
	long long	number;

	number = ft_atoll(num);
	if (number < left || number > right)
		return (0);	
	return (1);
}
