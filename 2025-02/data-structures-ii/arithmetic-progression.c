#include <stdio.h>

int arithmetic_progression_recursive
(
    int first_term,
    int reason,
    int total_terms
)
{
    if (total_terms == 1)
        return first_term;
    return first_term += arithmetic_progression_recursive(first_term, reason, total_terms - 1) + reason;
}

// retornar soma dos termos de forma recursiva

int main()
{
    int first_term, reason, total_terms;

    printf("enter the first term: ");
    scanf("%d", &first_term);

    printf("enter the total terms: ");
    scanf("%d", &total_terms);

    printf("enter the reason: ");
    scanf("%d", &reason);

    int result = arithmetic_progression_recursive(
        first_term, reason, total_terms
    );

    printf("result: %d\n", result);

    return 0;
}
