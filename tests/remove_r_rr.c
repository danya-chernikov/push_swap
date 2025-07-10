#include <stdio.h>
 
#define ARR_SIZE	32
 
typedef enum { SA, SB, SS, PA, PB, RA, RB, RR, RRA, RRB, RRR } ops_type;
 
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
 * `ra`/`rb`/`rr` [1 or more] -> `rra`/`rrb`/`rrr` [1 or more] */
void    remove_paired_r_rr(ops_type *arr, size_t *size)
{
    size_t      i;          /* Array counter */
    
    ops_type    fnd_op;     /* The first operation found */
    size_t      fnd_op_cnt; /* Counts how many operations of this type were found */
    size_t      fnd_op_ind; /* Index of the first found operation */
     
    ops_type    rev_op;     /* The reversed operation of the found operation fnd_op */
    size_t      rev_op_cnt; /* Counts how many reversed operations of the fnd_op were found */
    size_t      rev_op_ind; /* Index of the first reversed operation found after the last operation of the fnd_op type */
    
    i = 0;
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
            }
        }
        ++i;
    }
}
 
void    remove_paired_rr_r(ops_type *arr, size_t *size)
{
}
 
int main()
{
 
    ops_type	arr[ARR_SIZE] = { PA, SA, RA, RRA, SB, RRB, RB, RB, SS, RR, RRR, PB, RR, RR, RRR, RRR, RRR, PA, RA, RA, RA, PA, RRA, RRA, RA, SA, RRB, RRB, RB, RB, SB, SA };
    ops_type	arr2[ARR_SIZE] = { PA, SA, RA, RRA, SB, RRB, RB, RB, RRB, RB, RRR, RR, RR, RRR, RRR, RRR, PA, RA, RA, RA, PA, RRA, RRA, RA, SA, RRB, RRB, RB, RB, SB, SA, RR };
	ops_type	arr3[18] = { PA, SA, SB, PB, SS, PB, RRR, PA, RA, RA, RA, PA, RRA, SA, RRB, RB, SB, SA };
	ops_type	arr4[14] = { PA, PB, SA, RA, RA, RA, RRA, RRA, RRA, RRA, RRA, RR, SA, SS };
	ops_type	arr5[14] = { PA, PB, SA, RA, RA, RA, RA, RA, RRA, RRA, RRA, SB, PB, PA };
    
    size_t size;
    
    size = ARR_SIZE;
    ops_print(arr, size);
	printf("\n");
    remove_paired_r_rr(arr, &size);
	printf("\n");

    size = ARR_SIZE;
    ops_print(arr2, size);
	printf("\n");
    remove_paired_r_rr(arr2, &size);
	printf("\n");

    size = 18;
    ops_print(arr3, size);
	printf("\n");
    remove_paired_r_rr(arr3, &size);
	printf("\n");

    size = 14;
    ops_print(arr4, size);
	printf("\n");
    remove_paired_r_rr(arr4, &size);
	printf("\n");

    size = 14;
    ops_print(arr5, size);
	printf("\n");
    remove_paired_r_rr(arr5, &size);
	printf("\n");
	
    
	return (0); 
}
