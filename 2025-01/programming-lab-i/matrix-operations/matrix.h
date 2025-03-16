#ifndef MATRIX_H
#define MATRIX_H

typedef struct Matrix {
    int** data;
    int rows;
    int columns;
    int error;
} Matrix;

int getSizeOfMatrix(Matrix* matrix);

Matrix buildMatrix();

void showMatrix(Matrix* matrix);

void destroyMatrix(Matrix* matrix);

#endif
