#include <stdlib.h>

#include "service.h"

int main (void)
{
    CustomerQueue* customerQ = malloc(sizeof(CustomerQueue));

    if (customerQ == NULL) {
        printf("[!] Couldn't allocate a customer queue.\n");
        return 1;
    }

    customerQ->start = NULL;
    customerQ->end = NULL;
    customerQ->length = 0;

    startService(customerQ);

    return 0;
}
