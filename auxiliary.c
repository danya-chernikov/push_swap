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
int	num_in_range(const char *num, const int left, const int right)
{
	long long	number;

	number = ft_atoll(num);
	if (number < left || number > right)
		return (0);	
	return (1);
}

int	array_sorted(const int *arr, const size_t size)
{
	size_t	i;

	i = 0;
	while (i < size - 1)
	{
		if (arr[i] > arr[i + 1])
			return (0);
		++i;
	}
	return (1);
}

void	array_copy(int *arr_dst, const int *arr_src, const size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		arr_dst[i] = arr_src[i];
		++i;
	}
}

void	array_copy_atoi(int *arr_dst, char **arr_src, const size_t src_spos, const size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		arr_dst[i] = ft_atoi(arr_src[src_spos + i]);
		++i;
	}
}

void	print_n_times(const char *str, const size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		ft_printf("%s", str);
		++i;
	}
}

