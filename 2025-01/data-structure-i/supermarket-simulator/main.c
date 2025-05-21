#include <stdlib.h>

#include "service.h"

int main (void)
{
    CustomerQueue* customerQ = malloc(sizeof(CustomerQueue));
    customerQ->start = NULL;
    customerQ->end = NULL;
    customerQ->length = 0;

    startService(customerQ);

    return 0;
}
