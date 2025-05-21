#include "constants.h"

#ifndef CUSTOMER_H
#define CUSTOMER_H

// type definitions

typedef struct ProductQueue ProductQueue; // product.h

typedef struct CustomerNode CustomerNode;
typedef struct CustomerQueue CustomerQueue;

typedef struct Customer {
    char name[CUSTOMER_NAME_MAX];
    int totalItems;
    double totalBill;
    ProductQueue* products;
} Customer;

struct CustomerNode {
    Customer data;
    struct CustomerNode* next;
};

struct CustomerQueue {
    CustomerNode* start;
    CustomerNode* end;
    int length;
};

// function declarations

Customer createCustomer();
void enqueueCustomer(CustomerQueue*, Customer);
void dequeueCustomer(CustomerQueue*);

#endif

