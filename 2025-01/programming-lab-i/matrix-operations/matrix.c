#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

#define MAX_ROWS 100
#define MAX_COLUMNS 100
#define MAX_RANDOM_NUMBER 500

int i, j;

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

Matrix buildMatrix()
{
    printf("\n[Building Matrix]\n");

    Matrix matrix;
    matrix.error = 0;

    int result = readMatrixSize(&matrix);

    if (result == 1)
    {
        matrix.error = 1;
        return matrix;
    }

    matrix.data = (int **) malloc(matrix.rows * sizeof(int*));

    if (matrix.data == NULL) {
        printf("[ERR] Insufficient Memory");
        matrix.error = 1;
        return matrix;
    }

    for (i = 0; i < matrix.rows; ++i)
    {
        matrix.data[i] = (int*) malloc(matrix.columns * sizeof(int));

        if (matrix.data[i] == NULL)
        {
            printf("[ERR] Insufficient Memory");
            matrix.error = 1;
            return matrix;
        }

        for (j = 0; j < matrix.columns; ++j)
        {
            matrix.data[i][j] = rand() % MAX_RANDOM_NUMBER;
        }
    }

    return matrix;
}

void showMatrix(Matrix* matrix)
{
    printf("\n[Showing Matrix]\n");
    for (i = 0; i < matrix->rows; ++i)
    {
        for (j = 0; j < matrix->columns; ++j)
        {
            printf("%d \t", matrix->data[i][j]);
        }
        printf("\n");
    }
}

void destroyMatrix(Matrix* matrix)
{
    printf("\n[Destroying Matrix]\n");

    for (i = 0; i < matrix->rows; ++i)
    {
        free(matrix->data[i]);
        matrix->data[i] = NULL;
    }

    free(matrix->data);
    matrix->data = NULL;
}

