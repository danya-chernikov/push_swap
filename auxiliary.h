#if !defined(AUXILIARY_H)
# define AUXILIARY_H

int		count_digits(long long num);
int		get_digit(long long num, const int len, const int base, const int ind);
int		num_in_range(const char *num, int left, int right);
int		array_sorted(int *arr, size_t size);
void	print_n_times(const char *str, size_t n);

#endif
