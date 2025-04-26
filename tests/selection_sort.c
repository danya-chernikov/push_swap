#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARR_SIZE 100

int	swap_cnt = 0;

void	selection_sort(int *arr, size_t size)
{
	int	i;
	int	j;
	int	tmp;
	int	min;

	i = 0;
	min = i;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (arr[j] < arr[min])
			{
				min = j;
				swap_cnt++;
			}
			j++;
		}
		tmp = arr[min];
		arr[min] = arr[i];
		arr[i] = tmp;
		i++;
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

	selection_sort(arr, ARR_SIZE);

	for (int i = 0; i < ARR_SIZE; i++)
		printf("[%d] ", arr[i]);
	printf("\n\n");

	printf("swap_cnt = %d\n", swap_cnt);

	return (0);
}
