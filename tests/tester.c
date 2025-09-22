#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_BUF		2048
#define NUM_ARR_SIZE		1024
#define MAX_NUM_STR_LEN		32
#define MAX_CMD_LEN			4096
#define PUSH_SWAP_PATH		"push_swap"
#define CHECKER_PATH		"checker"

/*int	array_to_stack(t_stack *a, int *arr, size_t arr_size)
{

	
	return (1);
}*/

/* Divides a line by ',' and puts each number in the
 * integer array. Returns the number of integers found
 * and 0 in case of an error */
int	line_to_arr(char *line, int *arr, size_t arr_size)
{
	char	num[MAX_NUM_STR_LEN];
	int		num_ind;
	int		j;

	j = 0;
	num_ind = 0;
	for (int i = 0; i < strlen(line); ++i)
	{
		if (num_ind > arr_size)
			return (0);
		if (isdigit(line[i]))
		{
			num[j] = line[i];
			++j;
		}
		else
		{
			num[j] = '\0';
			arr[num_ind] = atoi(num);
			++num_ind;
			j = 0;
		}
	}
	num[j] = '\0';
	arr[num_ind] = atoi(num);
	return (num_ind);
}

char	*form_cmd(char *stack, char *push_swap, char *checker)
{
	char	*cmd;
	int		cind;

	cmd = (char *)malloc((MAX_CMD_LEN + 1) * sizeof (char));
	if (!cmd)
		return (NULL);
	cind = 0;
	cmd[0] = '.';
	cmd[1] = '/';
	cind += 2;
	for (int i = 0; i < strlen(push_swap); ++i)
		cmd[cind + i] = push_swap[i];
	cind += strlen(push_swap);
	cmd[cind++] = ' ';
	for (int i = 0; i < strlen(stack); ++i)
		cmd[cind + i] = stack[i];
	cind += strlen(stack);
	cmd[cind++] = ' ';
	cmd[cind++] = '|';
	cmd[cind++] = ' ';
	cmd[cind++] = '.';
	cmd[cind++] = '/';
	for (int i = 0; i < strlen(checker); ++i)
		cmd[cind + i] = checker[i];
	cind += strlen(checker);
	cmd[cind++] = ' ';
	for (int i = 0; i < strlen(stack); ++i)
		cmd[cind + i] = stack[i];
	cind += strlen(stack);
	cmd[cind] = '\0';
	return (cmd);
}

/* The `result` may be either 'OK' or 'KO' */
int	check(char *stack, char *push_swap, char *checker)
{
	FILE	*fp;
	char	*cmd;
	char	result[3];

	cmd = form_cmd(stack, push_swap, checker);
	printf("%s\n", cmd);
	free(cmd);
	fp = popen(cmd, "r");
	if (!fp)
	{
		perror("popen() failed");
		return (0);
	}
	while (fgets(result, sizeof (result), fp))
		strcat(result, );
	return (1);
}

/* Substitutes c1 by c2 in str */
void	substitute_str(char *str, char c1, char c2)
{
	for (int i = 0; i < strlen(str); ++i)
	{
		if (str[i] == c1)
			str[i] = c2;
	}
}

/* We suppose the numbers in the
 * file are separated with ','.
 * Each line represent a stack A
 * that needs to be sorted using
 * ./push_swap executable that
 * is located in the same directory.
 * Also ./checker must be located
 * in the same directory */
int	main(int argc, char **argv)
{
	FILE	*fptr;
	char	line[MAX_LINE_BUF];
	int		arr[NUM_ARR_SIZE];

	if (argc != 2)
	{
		printf("Error: specify a file from which to read\n");
		exit(EXIT_FAILURE);
	}
	fptr = fopen(argv[1], "r");
	if (!fptr)
	{
		printf("Error: cannot open the file\n");
		exit(EXIT_FAILURE);
	}
	while (fgets(line, sizeof (line), fptr))
	{
		substitute_str(line, ',', ' ');
		line[strlen(line) - 1] = '\0';
		printf("%s", line);
		int n = line_to_arr(line, arr, NUM_ARR_SIZE);
		check(line, PUSH_SWAP_PATH, CHECKER_PATH);
		/*if (check(arr))
			printf("OK\n");
		else
			printf("KO\n");
			*/
	}
	fclose(fptr);
	exit(EXIT_SUCCESS);
	return (0);
}
