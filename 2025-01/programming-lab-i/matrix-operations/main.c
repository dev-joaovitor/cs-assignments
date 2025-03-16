//#include <locale.h>
#include <stdio.h>
#include "matrix.h"
#include "operations/operations.h"

void showMenu(unsigned short int isCreatedA, unsigned short int isCreatedB)
{
    printf("[MENU] Options\n");

    if (isCreatedA == 0)
        printf("1 - Create matrix A\n");
    else
        printf("1 - Update matrix A\n");

    if (isCreatedB == 0)
        printf("2 - Create matrix B\n");
    else
        printf("2 - Update matrix B\n");

    if (isCreatedA != 0)
        printf("3 - Show matrix A\n");

    if (isCreatedB != 0)
        printf("4 - Show matrix B\n");

    if (isCreatedA != 0 && isCreatedB != 0)
    {
        printf("5 - Multiply (A * B)\n");
        printf("6 - Add (A + B)\n");
        printf("7 - Subtract (A - B)\n");
        printf("8 - Transpose matrix A\n");
        printf("9 - Transpose matrix B\n");
    }

    printf("10 - Generate identity matrix\n");
    printf("0 - Quit\n");
}

int main(int argc, char** argv)
{
    // setlocale(LC_ALL, "Portuguese");

    printf("\n[ --- Matrix operations --- ]\n\n");

    unsigned short int option = 0,
        shouldShowMenu = 1,
        shouldCancel = 0;

    Matrix A = {},
        B = {},
        M = {};

    while(1)
    {
        if (shouldCancel == 1) break;

        if (shouldShowMenu == 1)
            showMenu(
                A.columns == 0 ? 0 : 1,
                B.columns == 0 ? 0 : 1
            );
        else printf("11 - Show menu\n");

        printf("[MENU] Choose one option: ");
        scanf("%hu", &option);

        printf("\n");

        shouldShowMenu = 0;
        switch(option)
        {
            case 1:
                shouldShowMenu = 1;
                printf("[MATRIX A]\n");
                destroyMatrix(&A);
                A = buildMatrix(0, 0);

                if (A.error == 1) return 1;

                populateMatrixWithRandomNumbers(&A);
                break;
            case 2:
                shouldShowMenu = 1;
                printf("[MATRIX B]\n");
                destroyMatrix(&B);
                B = buildMatrix(0, 0);

                if (B.error == 1) return 1;

                populateMatrixWithRandomNumbers(&B);
                break;
            case 3:
                showMatrix(&A);
                break;
            case 4:
                showMatrix(&B);
                break;
            case 5:
                M = multiplyMatrices(&A, &B);

                if (M.error != 1)
                    showMatrix(&M);

                destroyMatrix(&M);
                break;
            case 6:
                M = addMatrices(&A, &B);

                if (M.error != 1)
                    showMatrix(&M);

                destroyMatrix(&M);
                break;
            case 7:
                M = subtractMatrices(&A, &B);

                if (M.error != 1)
                    showMatrix(&M);

                destroyMatrix(&M);
                break;
            case 8:
                M = transposeMatrix(&A);

                if (M.error != 1)
                    showMatrix(&M);

                destroyMatrix(&M);
                break;
            case 9:
                M = transposeMatrix(&B);

                if (M.error != 1)
                    showMatrix(&M);

                destroyMatrix(&M);
                break;
            case 10:
                M = generateIdentityMatrix();

                if (M.error != 1)
                    showMatrix(&M);

                destroyMatrix(&M);
                break;
            case 11:
                shouldShowMenu = 1;
                break;
            default:
                destroyMatrix(&A);
                destroyMatrix(&B);
                destroyMatrix(&M);
                shouldCancel = 1;
                break;
        }

        printf("\n\n");
    }

    printf("[ --- Tschuss! --- ]\n");

    return 0;
}

