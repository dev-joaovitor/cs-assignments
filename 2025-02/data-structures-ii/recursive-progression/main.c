#include <stdio.h>

int power(int base, int expoent)
{
    int result = 1;

    while (expoent > 0) {
        result *= base;

        --expoent;
    }

    return result;
}

int recursive_arithmetic_progression(
    int first_term, int reason, int total_terms
)
{
    int current_term = total_terms - 1;

    printf(
        "term[%d] = %d\n",
        total_terms,
        first_term + (current_term * reason)
    );

    if (total_terms > 1)
        return recursive_arithmetic_progression(
            first_term, reason, current_term
        ) + reason;

    return first_term;
}

int recursive_geometric_progression(
    int first_term, int reason, int total_terms
)
{
    int current_term = total_terms - 1;

    printf(
        "term[%d] = %d\n",
        total_terms,
        first_term * (power(first_term, current_term))
    );

    if (total_terms > 1)
        return recursive_geometric_progression(
            first_term, reason, current_term
        ) + power(first_term, current_term);

    return first_term;
}


int main()
{
    int first_term,
        reason,
        total_terms;
    
    printf("First Term: ");
    scanf("%d", &first_term);

    printf("Reason: ");
    scanf("%d", &reason);

    printf("Total Terms: ");
    scanf("%d", &total_terms);

    printf("\n");
    printf("A.P\n");
    int result_ap =
        recursive_arithmetic_progression(first_term, reason, total_terms);

    printf("\n");
    printf("G.P\n");
    int result_gp =
        recursive_geometric_progression(first_term, reason, total_terms);

    printf("\n");
    printf("Result by A.P Recursion: %d\n", result_ap);
    printf("Result by G.P Recursion: %d\n", result_gp);

    return 0;
}

