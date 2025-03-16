#include "matrix.h"
#include <stdio.h>
#include <locale.h>

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "Portuguese");

    Matrix A = buildMatrix(0,0);

    if (A.error == 1)
        return 1;

    printf("A:\n");
    populateMatrixWithRandomNumbers(&A);
    showMatrix(&A);

    Matrix A_t = transposeMatrix(&A);

    if (A_t.error == 1)
        return 1;

    printf("At:\n");
    showMatrix(&A_t);

    Matrix B = buildMatrix(0,0);

    if (B.error == 1)
        return 1;

    printf("B:\n");
    populateMatrixWithRandomNumbers(&B);
    showMatrix(&B);

    Matrix B_t = transposeMatrix(&B);

    if (B_t.error == 1)
        return 1;

    printf("Bt:\n");
    showMatrix(&B_t);

    Matrix C = multiplyMatrices(&A, &B);

    if (C.error == 1)
        return 1;

    printf("C:\n");
    showMatrix(&C);

    Matrix D = addMatrices(&A, &B);

    if (D.error == 1)
        return 1;

    printf("D:\n");
    showMatrix(&D);

    Matrix E = subtractMatrices(&A, &B);

    if (E.error == 1)
        return 1;

    printf("E:\n");
    showMatrix(&E);

    destroyMatrix(&A);
    destroyMatrix(&B);
    destroyMatrix(&C);
    destroyMatrix(&D);
    destroyMatrix(&E);

    return 0;
}

