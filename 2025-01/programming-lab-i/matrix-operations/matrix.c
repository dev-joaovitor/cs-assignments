#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

#define MAX_ROWS 100
#define MAX_COLUMNS 100
#define MAX_RANDOM_NUMBER 500

int i, j, k;

int readMatrixSize(Matrix* matrix)
{
    printf("\n[Reading Matrix Size]\n");
    printf("Enter the rows number: ");
    scanf("%d", &matrix->rows);

    if (matrix->rows <= 0)
    {
        printf("[ERR] Number of rows must be of greater than 0");
        return 1;
    }

    if (matrix->rows >= MAX_ROWS)
    {
        printf("[ERR] Number of rows must be of lower than %d", MAX_ROWS);
        return 1;
    }

    printf("Enter the columns number: ");
    scanf("%d", &matrix->columns);

    if (matrix->columns <= 0)
    {
        printf("[ERR] Number of columns must be of greater than 0");
        return 1;
    }

    if (matrix->columns >= MAX_COLUMNS)
    {
        printf("[ERR] Number of columns must be of lower than %d", MAX_COLUMNS);
        return 1;
    }
    return 0;
}

Matrix buildMatrix(int rows, int columns)
{
    //printf("\n[Building Matrix]\n");

    Matrix M;
    M.error = 0;

    if (rows == 0 || columns == 0)
    {
        int result = readMatrixSize(&M);

        if (result == 1)
        {
            M.error = 1;
            return M;
        }
    }
    else
    {
        M.columns = columns;
        M.rows = rows;
    }

    M.data = (int **) malloc(M.rows * sizeof(int*));

    if (M.data == NULL)
    {
        printf("[ERR] Insufficient Memory");
        M.error = 1;

        return M;
    }

    for (i = 0; i < M.rows; ++i)
    {
        M.data[i] = (int*) malloc(M.columns * sizeof(int));

        if (M.data[i] == NULL)
        {
            printf("[ERR] Insufficient Memory");
            M.error = 1;

            return M;
        }

        for (j = 0; j < M.columns; ++j)
        {
            M.data[i][j] = 0;
        }
    }

    return M;
}

void populateMatrixWithRandomNumbers(Matrix* M)
{
    for (i = 0; i < M->rows; ++i)
    {
        for (j = 0; j < M->columns; ++j)
        {
            M->data[i][j] = rand() % 10;
        }
    }
}

void showMatrix(Matrix* M)
{
    //printf("\n[Showing Matrix]\n");
    for (i = 0; i < M->rows; ++i)
    {
        for (j = 0; j < M->columns; ++j)
        {
            printf("%d \t", M->data[i][j]);
        }
        printf("\n");
    }
}

void destroyMatrix(Matrix* M)
{
    //printf("\n[Destroying Matrix]\n");

    for (i = 0; i < M->rows; ++i)
    {
        free(M->data[i]);
        M->data[i] = NULL;
    }

    free(M->data);
    M->data = NULL;
}

Matrix multiplyMatrices(Matrix* A, Matrix* B)
{
    Matrix C;
    C.error = 0;

    if (A->columns != B->rows)
    {
        printf("[ERR] For matrix multiplication, the number of columns in the first matrix must equal the number of rows in the second matrix");
        C.error = 1;
        return C;
    }

    C = buildMatrix(A->rows, B->columns);

    if (C.error == 1) return C;

    for (i = 0; i < A->rows; ++i)
    {
        for (j = 0; j < B->columns; ++j)
        {
            for (k = 0; k < B->rows; ++k)
            {
                C.data[i][j] += A->data[i][k] * B->data[k][j];

            }
        }
    }

    return C;
}

Matrix addMatrices(Matrix* A, Matrix* B)
{
    Matrix C;
    C.error = 0;

    if (A->rows != B->rows
        || A->columns != B->columns)
    {
        printf("[ERR] For matrix addition, both matrices must have an equal number of rows and columns");
        C.error = 1;
        return C;
    }

    C = buildMatrix(A->rows, A->columns);

    if (C.error == 1) return C;

    for (i = 0; i < A->rows; ++i)
    {
        for (j = 0; j < A->columns; ++j)
        {
            C.data[i][j] = (A->data[i][j] + B->data[i][j]);
        }
    }
    
    return C;
}

Matrix subtractMatrices(Matrix* A, Matrix* B)
{
    Matrix C;
    C.error = 0;

    if (A->rows != B->rows
        || A->columns != B->columns)
    {
        printf("[ERR] For matrix subtraction, both matrices must have an equal number of rows and columns");
        C.error = 1;
        return C;
    }

    C = buildMatrix(A->rows, A->columns);

    if (C.error == 1) return C;

    for (i = 0; i < A->rows; ++i)
    {
        for (j = 0; j < A->columns; ++j)
        {
            C.data[i][j] = (A->data[i][j] - B->data[i][j]);
        }
    }
    
    return C;
}

Matrix transposeMatrix(Matrix *M)
{
    Matrix M_t = buildMatrix(M->columns, M->rows);
    M_t.error = 0;

    if (M_t.error == 1) return M_t;

    for (i = 0; i < M_t.rows; ++i)
    {
        for (j = 0; j < M_t.columns; ++j)
        {
            M_t.data[i][j] = M->data[j][i];
        }
    }
    
    return M_t;
}

