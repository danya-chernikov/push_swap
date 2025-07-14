/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parser2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:21:58 by dchernik          #+#    #+#             */
/*   Updated: 2025/07/14 15:22:00 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "auxiliary.h"
#include "args_parser.h"

#include <stdlib.h>

char	**split_string_arg(char **argv)
{
	size_t	arg_i;
	size_t	num_cnt;
	char	**nums_to_sort;

	nums_to_sort = (char **)malloc(ARGS_INC_CHUNK_SIZE * sizeof (char *));
	if (!nums_to_sort)
		return (NULL);
	arg_i = 0;
	num_cnt = 0;
	while (arg_i < ft_strlen(argv[1]))
	{
		if (argv[1][arg_i] != ' ')
		{
			nums_to_sort[num_cnt] = alloc_found_num(nums_to_sort, num_cnt);
			if (!nums_to_sort[num_cnt])
				return (NULL);
			if (!copy_found_num(nums_to_sort, argv, num_cnt, &arg_i))
				return (NULL);
			++num_cnt;
		}
		++arg_i;
	}
	nums_to_sort[num_cnt] = NULL;
	return (nums_to_sort);
}

char	*alloc_found_num(char **nums_to_sort, size_t num_cnt)
{
	char	*found_num;
	size_t	j;

	found_num = (char *)malloc(MAX_INT_STR_LEN * sizeof (char));
	if (!found_num)
	{
		j = 0;
		while (j < num_cnt)
		{
			free(nums_to_sort[j]);
			nums_to_sort[j] = NULL;
			++j;
		}
		free(nums_to_sort);
		nums_to_sort = NULL;
		return (NULL);
	}
	return (found_num);
}

int	copy_found_num(char **nums_to_sort, char **argv,
		size_t num_cnt, size_t *arg_i)
{
	size_t	num_i;

	num_i = 0;
	while ((*arg_i < ft_strlen(argv[1])) && (argv[1][*arg_i] != ' '))
	{
		if (num_i > MAX_INT_STR_LEN)
		{
			string_args_free(nums_to_sort);
			return (0);
		}
		nums_to_sort[num_cnt][num_i] = argv[1][*arg_i];
		++(*arg_i);
		++num_i;
	}
	nums_to_sort[num_cnt][num_i] = '\0';
	return (1);
}

void	string_args_free(char **str_args)
{
	size_t	i;

	i = 0;
	while (str_args[i] != NULL)
	{
		if (str_args[i])
		{
			free(str_args[i]);
			str_args[i] = NULL;
		}
		++i;
	}
	free(str_args);
	str_args = NULL;
}
