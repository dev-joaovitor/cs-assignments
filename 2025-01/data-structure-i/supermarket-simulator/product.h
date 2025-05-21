#include "constants.h"

#ifndef PRODUCT_H
#define PRODUCT_H

// type definitions

typedef struct CustomerNode CustomerNode; // customer.h

typedef struct ProductQueue ProductQueue;
typedef struct ProductNode ProductNode;

typedef struct Product
{
    char name[PRODUCT_NAME_MAX];
    double price;
} Product;

struct ProductNode
{
    Product data;
    struct ProductNode* next;
};

struct ProductQueue
{
    ProductNode* start;
    ProductNode* end;
    int length;
};

// function declarations

Product createProduct();
void enqueueProduct(CustomerNode*, Product);
void freeProductQueue(ProductQueue*);
double calculateTotalPrice(ProductQueue*);

#endif
