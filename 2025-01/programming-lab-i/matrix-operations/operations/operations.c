#include <stdio.h>
#include "../matrix.h"

Matrix multiplyMatrices(Matrix* A, Matrix* B)
{
    int i, j, k;

    Matrix C = {};
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
    int i, j;

    Matrix C = {};
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
    int i, j;

    Matrix C = {};
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
    int i, j;

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

Matrix generateIdentityMatrix()
{
    int i, j;

    Matrix M = {};
    M.error = 0;

    int size = 0;

    printf("Enter the identity matrix size: ");
    scanf("%d", &size);

    if (size <= 0 || size >= MAX_ROWS)
    {
        printf("[ERR] The size is invalid");
        M.error = 1;
        return M;
    }
    
    M = buildMatrix(size, size);

    if (M.error == 1) return M;

    for (i = 0; i < M.rows; ++i)
    {
        for (j = 0; j < M.columns; ++j)
        {
            M.data[i][j] = i == j ? 1 : 0;
        }
    }

    return M;
}

