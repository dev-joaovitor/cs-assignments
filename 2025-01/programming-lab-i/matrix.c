#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define MAX_ROWS 100
#define MAX_COLUMNS 100
#define MAX_RANDOM_NUMBER 500

int getSizeOfMatrix(int * rows, int * columns)
{
    printf("Enter the rows number: ");
    scanf("%d", rows);

    if (*rows <= 0)
    {
        printf("[ERR] Number of rows must be of greater than 0");
        return 1;
    }

    if (*rows >= MAX_ROWS)
    {
        printf("[ERR] Number of rows must be of lower than %d", MAX_ROWS);
        return 1;
    }

    printf("Enter the columns number: ");
    scanf("%d", columns);

    if (*columns <= 0)
    {
        printf("[ERR] Number of columns must be of greater than 0");
        return 1;
    }

    if (*rows >= MAX_COLUMNS)
    {
        printf("[ERR] Number of columns must be of lower than %d", MAX_COLUMNS);
        return 1;
    }
    return 0;
}

int ** buildMatrix(int* rows, int* columns)
{
    int ** matrix = (int **) malloc(*rows * sizeof(float *));

    if (matrix == NULL) {
        printf("[ERR] Insufficient Memory");
        return NULL;
    }

    for (int i = 0; i < *rows; ++i)
    {
        matrix[i] = (int *) malloc(*columns * sizeof(int));

        if (matrix[i] == NULL)
        {
            printf("[ERR] Insufficient Memory");
            return NULL;
        }

        for (int j = 0; j < *columns; ++j)
        {
            matrix[i][j] = rand() % MAX_RANDOM_NUMBER;
        }
    }

    return matrix;
}

void showMatrix(int ** matrix, int * rows, int * columns)
{
    for (int i = 0; i < *rows; ++i)
    {
        for (int j = 0; j < *columns; ++j)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void destroyMatrix(int** matrix, int* rows)
{
    for (int i = 0; i < *rows; ++i)
    {
        free(matrix[i]);
    }
    free(matrix);
    printf("destroyed\n");
}

int main()
{
    setlocale(LC_ALL, "Portuguese");

    int rows = 0,
        columns = 0;

    int result = getSizeOfMatrix(&rows, &columns);

    if (result == 1) return 1;

    int ** matrix = buildMatrix(&rows, &columns);

    if (matrix == NULL) return 1;

    showMatrix(matrix, &rows, &columns);

    destroyMatrix(matrix, &rows);

    return 0;
}

