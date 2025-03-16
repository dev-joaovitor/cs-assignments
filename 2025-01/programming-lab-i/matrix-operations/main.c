#include "matrix.h"
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "Portuguese");

    Matrix matrix = buildMatrix();

    if (matrix.error == 1)
        return 1;

    showMatrix(&matrix);

    destroyMatrix(&matrix);

    return 0;
}

