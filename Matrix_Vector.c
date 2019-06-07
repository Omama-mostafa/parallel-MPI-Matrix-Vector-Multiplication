#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main()
{
    int row, col, vecLen;
    int i, j;

    printf("Enter Number of Rows : ");
    scanf("%d", &row);
    printf("\nEnter Number of Cols : ");
    scanf("%d", &col);
    printf("\nEnter Vector Length : ");
    scanf("%d", &vecLen);

    if(col != vecLen)
    {
        printf("\nInvalid Multiplication! \n");
        printf("MATRIX Cols NOT Equal VECTOR Rows. \n\n");
        return;
    }
    int *matrix = (int*)malloc(row * col * sizeof(int));
    int *vector = (int*)malloc(vecLen * sizeof(int));

    printf("\n");
    for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            printf("Enter Matrix values [%d][%d] : ", i, j);
            scanf("%d", (matrix + i * col + j));
        }
    }
    printf("\n");
    for(i=0; i<vecLen; i++)
    {
        printf("Enter Vector values [%d] : ", i);
        scanf("%d", (vector + i));
    }

    int *resMV = (int*)malloc(row * sizeof(int));
    #pragma omp parallel private(i, j)
    {
        #pragma omp for
        for(i=0; i<row; i++)
        {
            for(j=0; j<col; j++)
            {
                *(resMV + i) += ((*(matrix + i * col + j)) * (*(vector + j)));
                printf("local = %d with row = %d in thread number %d \n" , *(resMV + i), i, omp_get_thread_num());
            }
        }
    }
    printf("\n\nResult : \n");
    for(i=0; i<row; i++)
    {
        printf("%d\n", *(resMV + i));
    }
    return 0;
}
///print Matrix data

//    for(i=0; i<row; i++)
//    {
//        for(j=0; j<col; j++)
//        {
//            printf("%d \t" , *(matrix + i * col + j));
//            if(j == col -1)
//                printf("\n");
//        }
//    }

///print Vector data

//    for(i=0; i<vecLen; i++)
//    {
//        printf("%d \n", *(vector + i));
//    }
//

