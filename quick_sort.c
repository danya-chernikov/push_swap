#include "quick_sort.h"

static void		swap(int *a, int *b);
static size_t	partition(int *arr, int low, int high);

void	quick_sort(int *arr, int low, int high)
{
	int	pivot_ind;

	if (low < high)
	{
		pivot_ind = partition(arr, low, high);
		quick_sort(arr, low, pivot_ind - 1);
		quick_sort(arr, pivot_ind + 1, high);
	}
}

static void	swap(int *a, int *b)
{
    int	tmp;

	tmp = *a;
	*a = *b;
	*b = t;
}

static size_t	partition(int *arr, int low, int high)
{
	int	pivot;
	int	i;
	int	j;

	j = low;
	i = low - 1;
	pivot = arr[high];
	while (j <= high - 1)
	{
		if (arr[j] < pivot)
		{
			i++;
			swap(&arr[i], &arr[j]);
			swap_cnt++;
		}
		j++;
	}
	swap(&arr[i + 1], &arr[high]);
	swap_cnt++;
	return (i + 1);
}
