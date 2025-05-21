#include "product.h"
#include "customer.h"

#ifndef SERVICE_H
#define SERVICE_H

void startService(CustomerQueue*);
unsigned short serviceMenu();
void finishService(CustomerQueue*);

void listCustomers(CustomerQueue*);
void listProducts(ProductQueue*);

// return 1 for successful and 0 otherwise.
unsigned short checkout(CustomerNode*);

#endif
