#include "product.h"
#include "customer.h"

#ifndef SERVICE_H
#define SERVICE_H

void startService(CustomerQueue*);
unsigned short serviceMenu();
void finishService(CustomerQueue*);

void listCustomers(CustomerQueue*);
void listProducts(ProductQueue*);

void checkout(CustomerNode*);

#endif
