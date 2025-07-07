#if !defined(ARGS_PARSER_H)
# define ARGS_PARSER_H

#include "stack_basis.h"

int		is_number(const char *num);
int		check_ints_validity(int argc, char **argv);
int		check_duplicates(int *arr, size_t size);
void	args_to_stack(t_stack *stack, int argc, char **argv);

#endif
