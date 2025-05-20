#include <math.h>
#include <stdio.h>

#define MAX_ITERATIONS 50
#define LOG_FILE_NAME "newton-raphson.log"

int main(void)
{
    float a, b, c, d;

    double xn = 0.0,
        Eps = 0.0,
        x0 = 0.0,
        f_xn = 0.0,
        fdv_xn = 0.0;

    int n = 0;

    FILE* log_file = fopen(LOG_FILE_NAME, "w");

    if (log_file == NULL) {
        printf("Error opening the file");
        return 1;
    }

    fprintf(log_file, "+----------------+\n");
    fprintf(log_file, "| Newton-Raphson |\n");
    fprintf(log_file, "+----------------+\n");

    fprintf(log_file, "\n[Formula: Ax^3 + Bx^2 + Cx + D]\n");

    fprintf(log_file, "\n- Insira o valor de A: ");
    printf("- Insira o valor de A: ");
    scanf("%f", &a);
    fprintf(log_file, "%f", a);

    fprintf(log_file, "\n- Insira o valor de B: ");
    printf("- Insira o valor de B: ");
    scanf("%f", &b);
    fprintf(log_file, "%f", b);

    fprintf(log_file, "\n- Insira o valor de C: ");
    printf("- Insira o valor de C: ");
    scanf("%f", &c);
    fprintf(log_file, "%f", c);

    fprintf(log_file, "\n- Insira o valor de D: ");
    printf("- Insira o valor de D: ");
    scanf("%f", &d);
    fprintf(log_file, "%f", d);

    fprintf(log_file, "\n- Insira o chute inicial (xn): ");
    printf("- Insira o chute inicial (xn): ");
    scanf("%lf", &xn);
    fprintf(log_file, "%lf", xn);

    fprintf(log_file, "\n- Insira a margem de erro (Eps): ");
    printf("- Insira a margem de erro (Eps): ");
    scanf("%lf", &Eps);
    fprintf(log_file, "%lf\n", Eps);

    printf("\nVerifique o arquivo `%s` para ver o resultado!\n", LOG_FILE_NAME);

    do {
        if (n >= MAX_ITERATIONS) {
            fprintf(log_file, "Seu cálculo atingiu o número maximo de iteracoes (%d), modifique os parametros e tente novamente.\n", MAX_ITERATIONS);
            return 0;
        };

        x0 = xn;

        // f(x) = ax^3 + bx^2 + cx + d
        f_xn = (a*(x0*x0*x0) + b*(x0*x0) + c*(x0) + d);

        // f'(x) = 3ax^2 + 2bx + c
        fdv_xn = (3*a*(x0*x0)) + ((2*b)*(x0)) + c;

        // x - (f(x) / f'(x))
        xn = x0 - (f_xn / fdv_xn);

        ++n;

        fprintf(log_file, "\n--------------------------------\n");
        fprintf(log_file, "\nIteracao = %d \n\n", n);

        fprintf(log_file, "F(x) = %lf \n", f_xn);
        fprintf(log_file, "F'(x) = %lf \n\n", fdv_xn);

        fprintf(log_file, "X anterior = %lf \n", x0);
        fprintf(log_file, "X atual = %lf \n\n", xn);

        fprintf(log_file, "|xn - x0| = %lf \n", fabs(xn-x0));

    } while(fabs(xn - x0) > Eps);

    fprintf(log_file, "\n+------------------------------------+\n");
    fprintf(log_file, "| Total de iteracoes = %d \n", n);
    fprintf(log_file, "| Resultado final = %lf\n", xn);
    fprintf(log_file, "+------------------------------------+\n");

    fclose(log_file);

    return 0;
}

