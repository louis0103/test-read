// SMatrixADT.c
// Implement a Sparse Matrix ADT (SMatrix).
// Author is Mei.
// Create by Mei on 10, 12, 2018

#include<stdio.h>

#define SMTX_ERROR -1
#define MAX_SMTX_SIZE 100

#define DONE 'X'            /* quit the program */
#define ADDITION '+'
#define SUBTRACTION '-'
#define TRANSPOSE 'T'
#define Multiply '*'

typedef struct MAX
{
    int col;
    int row;
    int value;
} MAX;

typedef struct SMatrixType
{
    MAX R[MAX_SMTX_SIZE];
} SMatrixType;

int SMTX_read(SMatrixType A[]);     // read in a matrix from stdin and stores the matrix in A, returns SMTX_ERROR if something went wrong
int SMTX_print(SMatrixType A[]);    // print the sparse matrix A
int SMTX_add(SMatrixType A[],SMatrixType B[],SMatrixType C[]);      // C = A + B, returns SMTX_ERROR if something went wrong
int SMTX_subtract(SMatrixType A[],SMatrixType B[],SMatrixType C[]); // C = A - B, returns SMTX_ERROR if something went wrong
int SMTX_transpose(SMatrixType A[],SMatrixType B[]);                // B = transpose A, returns SMTX_ERROR if something went wrong
int SMTX_multiply(SMatrixType A[],SMatrixType B[],SMatrixType C[]); // C = A x B, returns SMTX_ERROR if something went wrong

int main ()
{
    SMatrixType	A, B, C, D;
    int  w1, w2;
    char op;         /* operation to be performed */

    /* read and print matrices */
    SMTX_read (&A);
    printf ("Matrix A:\n");
    SMTX_print (&A);
    SMTX_read (&B);
    printf ("Matrix B:\n");
    SMTX_print (&B);
    SMTX_read (&C);
    printf ("Matrix C:\n");
    SMTX_print (&C);


    /* Perform matrix operations */
    while (getchar() != '\n');
    scanf ("%c", &op);
    while (op != DONE)
    {
        switch (op)
        {
        case ADDITION:
            printf ("Addition\n");
            if (SMTX_add (&A, &B, &C)!= SMTX_ERROR)
                SMTX_print (&C);
            else
                printf ("Matrix ADDITION error!\n");
            break;
        case SUBTRACTION:
            if (SMTX_subtract (&A, &B, &C)!= SMTX_ERROR)
                SMTX_print (&C);
            else
                printf ("Matrix SUBTRACTION error!\n");
            break;
        case TRANSPOSE:
            if (SMTX_transpose (&A, &C)!= SMTX_ERROR)
                SMTX_print (&C);
            else
                printf ("Matrix TRNSPOSE error!\n");
            break;
        case Multiply:
            if (SMTX_multiply (&A, &B, &C)!= SMTX_ERROR)
                SMTX_print (&C);
            else
                printf ("Matrix Multiply error!\n");
            break;
        default :
            printf ("Invalid OPERATION error!\n");
        }
        printf ("Matrix A\n");
        SMTX_print (&A);
        printf ("Matrix B\n");
        SMTX_print (&B);
        printf ("Matrix C\n");
        SMTX_print (&C);

        while (getchar() != '\n');
        scanf ("%c", &op);
    } /* while */

    /** you should do more testing than the above **/
}// end main
//*********************************************************************************/

/** For this project, the input format will be
    Line 1: two integers, rows & cols, dimension the matrix
    Line 2 to Line rows+1: contains cols number of integers
Should take the input and convert to your proper ADT format.**/
int SMTX_read(SMatrixType A[])
{
    int r=0, l=0;
    scanf("%d %d", &r, &l);
    A->R[0].row = r;
    A->R[0].col = l;

    int n = 1,i = 0,j = 0;
    int v = 0;
    for(i = 0; i < r; i++)
    {
        for(j = 0; j<l; j++)
        {
            scanf("%d",&v);

            if(v != 0)
            {

                A->R[n].row = i;
                A->R[n].col = j;
                A->R[n].value = v;
                n++;
            }
        }
    }
    A->R[0].value = n-1;
}

/** print the sparse matrix A in the following format
    Line 1: print"Rows = ??, Cols = ??, # of non-zero entries = ??"
    Line 2 ~ ??: print "<Ri, Ci, entry-value>," one 3-tuple per line.**/
int SMTX_print(SMatrixType A[])
{
    printf("Rows=%d, Cols=%d, # of non-zero entries=%d\n", A->R[0].row, A->R[0].col, A->R[0].value);
    printf("<Ri, Ci, entry-value>\n");
    int i;
    int v = A->R[0].value;
    if(v>0)
    {
        for(i=1; i<=v; i++)
        {
            printf("%2d, %2d, %2d\n",A->R[i].row,A->R[i].col, A->R[i].value);
        }
    }
}

int SMTX_add(SMatrixType A[], SMatrixType B[], SMatrixType C[])
{
    int i = 1,j = 1;

    int row_A = A->R[0].row, row_B = B->R[0].row, col_A = A->R[0].col, col_B = B->R[0].col;

    if(row_A != row_B || col_A != col_B)
    {
        return SMTX_ERROR;
    }

    C->R[0].row = row_B;
    C->R[0].col = col_B;
    int k=1;

    while (i <= A->R[0].value && j <= B->R[0].value)
    {
        if (A->R[i].row > B->R[j].row ||(A->R[i].row == B->R[j].row && A->R[i].col > B->R[j].col))
            C->R[k++] = B->R[j++];
        else if (A->R[i].row < B->R[j].row ||(A->R[i].row == B->R[j].row && A->R[i].col < B->R[j].col))
            C->R[k++] = A->R[i++];
        else
        {
            int sum = A->R[i].value + B->R[j].value;
            if (sum != 0)
            {
                C->R[k].row = A->R[i].row;
                C->R[k].col = A->R[i].col;
                C->R[k].value = sum;
                k++;
            }
            i++;
            j++;
        }
    }
    while (i <= A->R[0].value)
        C->R[k++] = A->R[i++];
    while (j <= B->R[0].value)
        C->R[k++] = B->R[j++];
    C->R[0].row = A->R[0].row;
    C->R[0].col = A->R[0].col;
    C->R[0].value = k - 1;
}

int SMTX_subtract(SMatrixType A[], SMatrixType B[], SMatrixType C[])
{
    int i = 1,j = 1;

    int row_A = A->R[0].row, row_B = B->R[0].row, col_A = A->R[0].col, col_B = B->R[0].col;

    if(col_A!=col_B||row_A!=row_B)
    {
        return SMTX_ERROR;
    }

    C->R[0].row = row_B;
    C->R[0].col = col_B;
    int sum = 0;
    int k = 1;
    while (i <= A->R[0].value && j <= B->R[0].value)
    {
        if (A->R[i].row > B->R[j].row ||(A->R[i].row == B->R[j].row && A->R[i].col > B->R[j].col))
        {
            C->R[k].row = B->R[j].row;
            C->R[k].col = B->R[j].col;
            sum=B->R[j].value;
            C->R[k].value = -sum;
            k++;
            j++;
        }
        else if (A->R[i].row < B->R[j].row ||(A->R[i].row == B->R[j].row && A->R[i].col < B->R[j].col))
            C->R[k++] = A->R[i++];
        else
        {
            sum = A->R[i].value - (B->R[j].value);
            if (sum != 0)
            {
                C->R[k].row = A->R[i].row;
                C->R[k].col = A->R[i].col;
                C->R[k].value = sum;
                k++;
            }
            i++;
            j++;
        }
    }
    while (i <= A->R[0].value)
        C->R[k++] = A->R[i++];
    while (j <= B->R[0].value)
    {
        C->R[k].row = B->R[j].row;
        C->R[k].col = B->R[j].col;
        C->R[k].value = -1*(B->R[j].value);
        k++;
        j++;
    }
    C->R[0].row = A->R[0].row;
    C->R[0].col = A->R[0].col;
    C->R[0].value = k-1;
}

int SMTX_transpose(SMatrixType A[],SMatrixType B[])
{
    int row_terms[MAX_SMTX_SIZE], starting_pos[MAX_SMTX_SIZE];
    int i, j, num_col = A->R[0].col, num_terms = A->R[0].value;
    B->R[0].row = num_col;
    B->R[0].col = A->R[0].row;
    B->R[0].value = num_terms;
    if(num_terms > 0)
    {
        for(i=0; i <= num_col; i++)
        {
            row_terms[i] = 0;
        }
        for(i=1; i<= num_terms; i++)
        {
            row_terms[A->R[i].col]++;
        }
        starting_pos[0] = 1;
        for(i=1; i < num_col; i++)
        {
            starting_pos[i] = starting_pos[i-1] + row_terms[i-1];
        }
        for(i=1; i <= num_terms; i++)
        {
            j = starting_pos[A->R[i].col]++;
            B->R[j].row = A->R[i].col;
            B->R[j].col = A->R[i].row;
            B->R[j].value = A->R[i].value;
        }
    }
    else return SMTX_ERROR;
}

/**you should use the quick algorithm given in lecture**/
int SMTX_multiply(SMatrixType A[],SMatrixType B[],SMatrixType C[])
{
    int i = 1,j = 1,k = 1;
    int tota = A->R[0].value,totb = B->R[0].value;
    int row_A = A->R[0].row,col_A = A->R[0].col;
    int col_B = B->R[0].col;
    SMatrixType new_B[MAX_SMTX_SIZE];

    if(col_A != B->R[0].row)
    {
        return SMTX_ERROR;
    }

    SMTX_transpose(B,new_B);
    int x, sum;
    i = 1;k = 1;
    while(i <= tota)
    {
        x = i;
        j = 1;
        while(j <= totb)
        {
            row_A = A->R[i].row;
            col_B = new_B->R[j].row;
            sum = 0;
            while(i <= tota && j <= totb && row_A == A->R[i].row && col_B == new_B->R[j].row)
            {
                if(A->R[i].col == new_B->R[j].col)
                {
                    sum = sum + (A->R[i].value) * (new_B->R[j].value);
                    i++;
                    j++;
                }
                else
                {
                    if(A->R[i].col < new_B->R[j].col)
                        i++;
                    else
                        j++;
                }
            }
            if(sum != 0)
            {
                C->R[k].row = row_A;
                C->R[k].col = col_B;
                C->R[k].value = sum;
                k++;
            }
            if(j < totb)
                i = x;
            while(col_B == B->R[j].row && j <= totb)
                j++;
        }
        while(row_A == A->R[i].row && i <= tota)
            i++;
    }
    C->R[0].row = A->R[0].row;
    C->R[0].col = A->R[0].col;
    C->R[0].value = k-1;
}


