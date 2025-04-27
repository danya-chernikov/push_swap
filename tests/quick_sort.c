#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define	ARR_SIZE 100

int	swap_cnt = 0;

/*void	swap(int *arr, int ind1, int ind2)
{
	arr[ind1] ^= arr[ind2];
	arr[ind2] ^= arr[ind1];
	arr[ind1] ^= arr[ind2];
}*/

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

size_t	partition(int *arr, int low, int high)
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

int	main()
{
	srand(time(NULL));

	int	arr[ARR_SIZE];

	for (int i = 0; i < ARR_SIZE; i++)
		arr[i] = ARR_SIZE - i;

	for (int i = 0; i < ARR_SIZE; i++)
		printf("[%d] ", arr[i]);
	printf("\n\n");

	quick_sort(arr, 0, ARR_SIZE - 1);

	for (int i = 0; i < ARR_SIZE; i++)
		printf("[%d] ", arr[i]);
	printf("\n\n");

	printf("swap_cnt = %d\n", swap_cnt);
	
	return (0);
}
