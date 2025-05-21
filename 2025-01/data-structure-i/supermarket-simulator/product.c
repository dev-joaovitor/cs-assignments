#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "product.h"
#include "customer.h"

Product createProduct()
{
    Product product;

    printf("Enter the product name: ");
    fgets(product.name, PRODUCT_NAME_MAX, stdin);

    printf("Enter the product price: ");
    scanf("%lf", &product.price);

    return product;
}

void enqueueProduct(CustomerNode* customer, Product productData)
{
    ProductNode* product = malloc(sizeof(ProductNode));

    if (product == NULL) {
        printf("[!] Couldn't allocate a product node.\n");
        return;
    }

    product->data = productData;
    product->next = NULL;

    ProductQueue* productQ = customer->data.products;
    productQ->length++;

    if (productQ->start == NULL) {
        productQ->start = product;
        productQ->end = product;
        return;
    }
    productQ->end->next = product;
    productQ->end = product;
}

void freeProductQueue(ProductQueue* productQ)
{
    if (productQ->start == NULL)
        return;

    ProductNode* product = productQ->start;

    while (product != NULL) {
        ProductNode* tempProduct = product;
        product = product->next;

        free(tempProduct);
    }
    free(productQ);
}

double calculateTotalPrice(ProductQueue * productQ)
{
    double total = 0.0;

    ProductNode* product = productQ->start;

    while (product != NULL) {
        total += product->data.price;

        product = product->next;
    }

    return total;
}

