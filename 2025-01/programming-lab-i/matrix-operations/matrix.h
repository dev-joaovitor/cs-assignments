#ifndef MATRIX_H
#define MATRIX_H

#define MAX_ROWS 100
#define MAX_COLUMNS 100
#define MAX_RANDOM_NUMBER 100

typedef struct Matrix {
    int** data;
    int rows;
    int columns;
    int error;
} Matrix;

Matrix buildMatrix(int rows, int columns);

int readMatrixSize(Matrix* M);

void populateMatrixWithRandomNumbers(Matrix* M);

void showMatrix(Matrix* M);

void destroyMatrix(Matrix* M);

#endif
