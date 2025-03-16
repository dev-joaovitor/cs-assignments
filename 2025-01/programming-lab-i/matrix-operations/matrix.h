#ifndef MATRIX_H
#define MATRIX_H

typedef struct Matrix {
    int** data;
    int rows;
    int columns;
    int error;
} Matrix;

Matrix buildMatrix(int rows, int columns);

int readMatrixSize(Matrix* M);

void populateMatrixWithRandomNumbers(Matrix* M);

Matrix multiplyMatrices(Matrix* A, Matrix* B);
Matrix addMatrices(Matrix* A, Matrix* B);
Matrix subtractMatrices(Matrix* A, Matrix* B);
Matrix transposeMatrix(Matrix* M);

void showMatrix(Matrix* M);

void destroyMatrix(Matrix* M);

#endif
