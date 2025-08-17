#include <stdio.h>

void factorial_not_recursive()
{
    printf("--- factorial not recursive ---\n");

    double fac, n;

    printf("enter number: ");
    scanf("%lf", &n);

    for (fac = 1; n > 1.0; n--)
    {
        printf(
            "fat(%.1f) * n(%.1f) = %.1f\n",
            fac,
            n,
            fac * n
        );

        fac *= n;
    }

    printf("result = %.1f\n------\n", fac);
}

double _factorial_recursive(double n)
{
    if (n > 1)
        return n *= _factorial_recursive(n - 1);
    return n;
}

void factorial_recursive()
{
    printf("--- factorial recursive ---\n");

    double fac, n;

    printf("enter number: ");
    scanf("%lf", &n);

    fac = _factorial_recursive(n);

    printf("result = %.1f\n------\n", fac);
}

int main()
{
    factorial_not_recursive();
    factorial_recursive();

    return 0;
}

