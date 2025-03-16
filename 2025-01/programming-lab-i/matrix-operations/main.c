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

    Matrix B = buildMatrix(0,0);

    if (B.error == 1)
        return 1;

    printf("B:\n");
    populateMatrixWithRandomNumbers(&B);
    showMatrix(&B);

    Matrix C = multiplyMatrices(&A, &B);

    if (C.error == 1)
        return 1;

    printf("C:\n");
    showMatrix(&C);


    destroyMatrix(&A);
    destroyMatrix(&B);
    destroyMatrix(&C);

    return 0;
}

