#if !defined(AUXILIARY_H)
# define AUXILIARY_H

int		count_digits(long long num);
int		get_digit(long long num, const int len, const int base, const int ind);
int		num_in_range(const char *num, int left, int right);
int		array_sorted(const int *arr, const size_t size);
void	array_copy(int *arr_dst, const int *arr_src, const size_t size);
void	array_copy_atoi(int *arr_dst, char **arr_src, const size_t src_spos, const size_t size);
void	print_n_times(const char *str, const size_t n);

#endif
