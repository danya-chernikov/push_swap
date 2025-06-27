#include <stdio.h>
#include <stdlib.h>

void	swap(int *v, const int i, const int j)
{
	int	tmp;

	tmp = v[i];
	v[i] = v[j];
	v[j] = tmp;
}

void	print(const int *v, const int size)
{
	if (v != 0)
	{
		for (int i = 0; i < size; ++i)
			printf("%4d", v[i]);
		printf("\n");
	}
}

void	rotate_left(int *v, const int start, const int n)
{
	int	tmp;
	
	tmp = v[start];
	for (int i = start; i < n - 1; ++i)
		v[i] = v[i + 1];
	v[n - 1] = tmp;
}

void	permute(int *v, const int start, const int n)
{
	print(v, n);
	if (start < n)
	{
		for (int i = n - 2; i >= start; --i)
		{
			for (int j = i + 1; j < n; ++j)
			{
				swap(v, i, j);
				permute(v, i + 1, n);
			}
			rotate_left(v, i, n);
		}
	}
}

void	init(int *v, const int size)
{
	for (int i = 0; i < size; ++i)
		v[i] = i + 1;
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return (1);

	int	arr_size = atoi(argv[1]);
	int *v = (int *)malloc(sizeof(int) * arr_size);
	init(v, arr_size);
	permute(v, 0, arr_size);
	free(v);

	return (0);
}
