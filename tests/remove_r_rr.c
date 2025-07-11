#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
#define ARR_SIZE	32
 
typedef enum { SA, SB, SS, PA, PB, RA, RB, RR, RRA, RRB, RRR, END } ops_type;
 
#define SA_OP_STR       "sa"
#define SB_OP_STR       "sb"
#define SS_OP_STR       "ss"
#define PA_OP_STR       "pa"
#define PB_OP_STR       "pb"
#define RA_OP_STR       "ra"
#define RB_OP_STR       "rb"
#define RR_OP_STR       "rr"
#define RRA_OP_STR      "rra"
#define RRB_OP_STR      "rrb"
#define RRR_OP_STR      "rrr"
 
void    print_op_by_type(const ops_type op)
{
    if (op == SA) 
        printf("%s\n", SA_OP_STR);
    if (op == SB)
        printf("%s\n", SB_OP_STR);
    if (op == SS)
        printf("%s\n", SS_OP_STR);
    if (op == PA)
        printf("%s\n", PA_OP_STR);
    if (op == PB)
        printf("%s\n", PB_OP_STR);
    if (op == RA)
        printf("%s\n", RA_OP_STR);
    if (op == RB)
        printf("%s\n", RB_OP_STR);
    if (op == RR)
        printf("%s\n", RR_OP_STR);
    if (op == RRA)
        printf("%s\n", RRA_OP_STR);
    if (op == RRB)
        printf("%s\n", RRB_OP_STR);
    if (op == RRR)
        printf("%s\n", RRR_OP_STR);
}
 
void    ops_print(const ops_type *arr, const size_t size)
{
    size_t  i;
    
    i = 0;
    while (i < size)
    {
        print_op_by_type(arr[i]);
        ++i;
    }
}
 
void    remove_by_ind(ops_type *arr, size_t *size, const size_t index)
{
    size_t i = index;
    while (i < *size - 1)
    {
        arr[i] = arr[i + 1];
        ++i;
    }
    --(*size);
}

/* If op2 is reversed operation for op1 returns 1 */
int ops_reciprocal(ops_type op1, ops_type op2)
{
    if ((op1 == RA && op2 == RRA) || (op1 == RRA && op2 == RA))
        return (1);
    if ((op1 == RB && op2 == RRB) || (op2 == RB && op1 == RRB))
        return (1);
    if ((op1 == RR && op2 == RRR) || (op2 == RR && op1 == RRR))
        return (1);
    return (0);
}
 
/* Removes all chains that do not make sense of the form
 * `ra`/`rb`/`rr` [1 or more] -> `rra`/`rrb`/`rrr` [1 or more].
 * Returns newly allocated array of operations without those
 * were removed. Returns NULL when encountered with an error */
ops_type	*remove_paired_r_rr(ops_type *arr, size_t *size)
{
    size_t      i;          /* Array counter */
    
    ops_type    fnd_op;     /* The first operation found */
    size_t      fnd_op_cnt; /* Counts how many operations of this type were found */
    size_t      fnd_op_ind; /* Index of the first found operation */
     
    ops_type    rev_op;     /* The reversed operation of the found operation fnd_op */
    size_t      rev_op_cnt; /* Counts how many reversed operations of the fnd_op were found */
    size_t      rev_op_ind; /* Index of the first reversed operation found after the last operation of the fnd_op type */

	size_t		del_ops_cnt; /* Counter of deleted operations */
	size_t		new_arr_ind;

	char		*ops_inds;
	ops_type	*new_arr;

	ops_inds = (char *)calloc(*size, sizeof (char));
	if (!ops_inds)
		return (NULL);
    
    i = 0;
	del_ops_cnt = 0;
    fnd_op_cnt = 0;
	rev_op_cnt = 0;
    while (i < *size)
    {
        if (arr[i] == RA || arr[i] == RB || arr[i] == RR || arr[i] == RRA || arr[i] == RRB || arr[i] == RRR)
        {
            fnd_op = arr[i];
            fnd_op_ind = i;
            while (arr[i] == fnd_op && i < *size)
            {
                ++fnd_op_cnt;
                ++i;
            }
            if (i < *size)
            {
                if (ops_reciprocal(fnd_op, arr[i]))
                {
                    rev_op = arr[i];
                    rev_op_ind = i;
                    while (arr[i] == rev_op && i < *size)
                    {
                        ++rev_op_cnt;
                        ++i;
                    }
                    if (rev_op_cnt >= fnd_op_cnt)
                    {
                        for (size_t di = fnd_op_ind; di < fnd_op_ind + fnd_op_cnt * 2; ++di)
                        {
                            //remove_by_ind(ops_type *arr, size_t *size, const size_t index)
                            printf("%lu\n", di);
							ops_inds[di] = 1;
							++del_ops_cnt;
                        }
                        i = fnd_op_ind + fnd_op_cnt * 2;
						fnd_op_cnt = 0;
						rev_op_cnt = 0;
                        continue ;
                    }
                    else // rev_op_cnt < fnd_op_cnt
                    {
                        for (size_t di = fnd_op_ind + (fnd_op_cnt - rev_op_cnt); di < rev_op_ind + rev_op_cnt; ++di)
                        {
                            //remove_by_ind(ops_type *arr, size_t *size, const size_t index)
                            printf("%lu\n", di);
							ops_inds[di] = 1;
							++del_ops_cnt;
                        }
						i = rev_op_ind + rev_op_cnt;
						fnd_op_cnt = 0;
						rev_op_cnt = 0;
						continue ;
                    }
                }
                else // !ops_reciprocal(fnd_op, arr[i])
                {
                    fnd_op_cnt = 0;
                    rev_op_cnt = 0;
                    ++i;
                    continue ;
                }
            } // if (i < *size)

        } // if (arr[i] == RA || arr[i] == RB || arr[i] == RR || arr[i] == RRA || arr[i] == RRB || arr[i] == RRR)

        ++i;

    } // while (i < *size)

	new_arr = (ops_type *)malloc((*size - del_ops_cnt + 1) * sizeof (ops_type));
	if (!new_arr)
		return (NULL);

	i = 0;
	new_arr_ind = 0;
	while (i < *size)
	{
		if (ops_inds[i] == 0)
		{
			new_arr[new_arr_ind] = arr[i];
			++new_arr_ind;
		}
		++i;
	}
	new_arr[new_arr_ind] = END;

	return (new_arr);
}
 
int main()
{
 
    ops_type	arr[ARR_SIZE] = { PA, SA, RA, RRA, SB, RRB, RB, RB, SS, RR, RRR, PB, RR, RR, RRR, RRR, RRR, PA, RA, RA, RA, PA, RRA, RRA, RA, SA, RRB, RRB, RB, RB, SB, SA };
    ops_type	arr2[ARR_SIZE] = { PA, SA, RA, RRA, SB, RRB, RB, RB, RRB, RB, RRR, RR, RR, RRR, RRR, RRR, PA, RA, RA, RA, PA, RRA, RRA, RA, SA, RRB, RRB, RB, RB, SB, SA, RR };
	ops_type	arr3[18] = { PA, SA, SB, PB, SS, PB, RRR, PA, RA, RA, RA, PA, RRA, SA, RRB, RB, SB, SA };
	ops_type	arr4[14] = { PA, PB, SA, RA, RA, RA, RRA, RRA, RRA, RRA, RRA, RR, SA, SS };
	ops_type	arr5[14] = { PA, PB, SA, RA, RA, RA, RA, RA, RRA, RRA, RRA, SB, PB, PA };
	ops_type	arr6[16] = { PB, SS, SB, RA, RA, RRA, RRA, RA, RA, RA, RRA, RRA, RRA, RA, PA, PB };
	ops_type	arr7[8] = { RA, RA, RRA, RRA, SA, SB, RRB, RB };
	ops_type	arr8[6] = { RA, RA, RRA, RRA, RRB, RB };
	ops_type	arr9[2] = { RA, RRA };
	ops_type	arr10[20] = { PA, RA, RA, RA, RA, RRA, RRA, RRA, RRA, RRA, RRA, RRA, RRA, RA, RA, RA, RA, RA, RA, RA };

	ops_type	*new_arr;
    
    size_t size;
	size_t new_size;
    
	printf("############################## 1 ##############################\n");
    size = ARR_SIZE;
    ops_print(arr, size);
	printf("\n\n");
    new_arr = remove_paired_r_rr(arr, &size);
	if (!new_arr)
	{
		fprintf(stderr, "Error: Cannot allocate memory\n");
		exit (1);
	}
	new_size = 0;
	for (; new_arr[new_size] != END; ++new_size);
	printf("\nnew size: %lu\n\n", new_size);
	ops_print(new_arr, new_size);
	free(new_arr);
	new_arr = NULL;
	printf("\n\n");

	printf("############################## 2 ##############################\n");
    size = ARR_SIZE;
    ops_print(arr2, size);
	printf("\n");
    new_arr = remove_paired_r_rr(arr2, &size);
	if (!new_arr)
	{
		fprintf(stderr, "Error: Cannot allocate memory\n");
		exit (1);
	}
	new_size = 0;
	for (; new_arr[new_size] != END; ++new_size);
	printf("\nnew size: %lu\n\n", new_size);
	ops_print(new_arr, new_size);
	free(new_arr);
	new_arr = NULL;
	printf("\n\n");


	printf("############################## 3 ##############################\n");
    size = 18;
    ops_print(arr3, size);
	printf("\n\n");
    new_arr = remove_paired_r_rr(arr3, &size);
	if (!new_arr)
	{
		fprintf(stderr, "Error: Cannot allocate memory\n");
		exit (1);
	}
	new_size = 0;
	for (; new_arr[new_size] != END; ++new_size);
	printf("\nnew size: %lu\n\n", new_size);
	ops_print(new_arr, new_size);
	free(new_arr);
	new_arr = NULL;
	printf("\n\n");

	printf("############################## 4 ##############################\n");
    size = 14;
    ops_print(arr4, size);
	printf("\n\n");
    new_arr = remove_paired_r_rr(arr4, &size);
	if (!new_arr)
	{
		fprintf(stderr, "Error: Cannot allocate memory\n");
		exit (1);
	}
	new_size = 0;
	for (; new_arr[new_size] != END; ++new_size);
	printf("\nnew size: %lu\n\n", new_size);
	ops_print(new_arr, new_size);
	free(new_arr);
	new_arr = NULL;
	printf("\n\n");

	printf("############################## 5 ##############################\n");
    size = 14;
    ops_print(arr5, size);
	printf("\n\n");
    remove_paired_r_rr(arr5, &size);
    new_arr = remove_paired_r_rr(arr5, &size);
	if (!new_arr)
	{
		fprintf(stderr, "Error: Cannot allocate memory\n");
		exit (1);
	}
	new_size = 0;
	for (; new_arr[new_size] != END; ++new_size);
	printf("\nnew size: %lu\n\n", new_size);
	ops_print(new_arr, new_size);
	free(new_arr);
	new_arr = NULL;
	printf("\n\n");

	printf("############################## 6 ##############################\n");
    size = 16;
    ops_print(arr6, size);
	printf("\n\n");
    new_arr = remove_paired_r_rr(arr6, &size);
	if (!new_arr)
	{
		fprintf(stderr, "Error: Cannot allocate memory\n");
		exit (1);
	}
	new_size = 0;
	for (; new_arr[new_size] != END; ++new_size);
	printf("\nnew size: %lu\n\n", new_size);
	ops_print(new_arr, new_size);
	free(new_arr);
	new_arr = NULL;
	printf("\n\n");

	printf("############################## 7 ##############################\n");
    size = 8;
    ops_print(arr7, size);
	printf("\n\n");
    new_arr = remove_paired_r_rr(arr7, &size);
	if (!new_arr)
	{
		fprintf(stderr, "Error: Cannot allocate memory\n");
		exit (1);
	}
	new_size = 0;
	for (; new_arr[new_size] != END; ++new_size);
	printf("\nnew size: %lu\n\n", new_size);
	ops_print(new_arr, new_size);
	free(new_arr);
	new_arr = NULL;
	printf("\n\n");

	printf("############################## 8 ##############################\n");
    size = 6;
    ops_print(arr8, size);
	printf("\n\n");
    new_arr = remove_paired_r_rr(arr8, &size);
	if (!new_arr)
	{
		fprintf(stderr, "Error: Cannot allocate memory\n");
		exit (1);
	}
	new_size = 0;
	for (; new_arr[new_size] != END; ++new_size);
	printf("\nnew size: %lu\n\n", new_size);
	ops_print(new_arr, new_size);
	free(new_arr);
	new_arr = NULL;
	printf("\n\n");

	printf("############################## 9 ##############################\n");
    size = 2;
    ops_print(arr9, size);
	printf("\n\n");
    new_arr = remove_paired_r_rr(arr9, &size);
	if (!new_arr)
	{
		fprintf(stderr, "Error: Cannot allocate memory\n");
		exit (1);
	}
	new_size = 0;
	for (; new_arr[new_size] != END; ++new_size);
	printf("\nnew size: %lu\n\n", new_size);
	ops_print(new_arr, new_size);
	free(new_arr);
	new_arr = NULL;
	printf("\n\n");

	printf("############################## 10 ##############################\n");
    size = 20;
    ops_print(arr10, size);
	printf("\n\n");
    new_arr = remove_paired_r_rr(arr10, &size);
	if (!new_arr)
	{
		fprintf(stderr, "Error: Cannot allocate memory\n");
		exit (1);
	}
	new_size = 0;
	for (; new_arr[new_size] != END; ++new_size);
	printf("\nnew size: %lu\n\n", new_size);
	ops_print(new_arr, new_size);
	free(new_arr);
	new_arr = NULL;
	printf("\n");
    
	return (0); 
}
