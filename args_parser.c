#include "libft.h"
#include "auxiliary.h"
#include "args_parser.h"

#include <limits.h>

int		is_number(const char *num)
{
	size_t	i;

	if ((num[0] != '-') || !ft_isdigit((num[0])))
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

int		check_ints_validity(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_number(argv[i]) || !is_num_in_range(argv[i], INT_MIN, INT_MAX))
			return (0);
		++i;
	}
	return (1);
}

void	args_to_stack(t_stack *stack, int argc, char **argv)
{
	int	i;

	i = argc - 1;
	while (i > 0)
	{
		stack_push(stack, ft_atoi(argv[i]));
		--i;
	}
}
