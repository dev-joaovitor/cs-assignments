#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int readMatrixSize(Matrix* matrix)
{
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
    int i, j;

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

void fillMatrixWithRandomNumbers(Matrix* M)
{
    int i, j;

    for (i = 0; i < M->rows; ++i)
    {
        for (j = 0; j < M->columns; ++j)
        {
            M->data[i][j] = rand() % MAX_RANDOM_NUMBER;
        }
    }
}

void showMatrix(Matrix* M)
{
    int i, j;

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
    if (M->data == NULL) return;

    int i, j;

    for (i = 0; i < M->rows; ++i)
    {
        free(M->data[i]);
        M->data[i] = NULL;
    }

    free(M->data);
    M->data = NULL;
}

