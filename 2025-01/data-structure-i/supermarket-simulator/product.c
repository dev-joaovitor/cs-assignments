#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "product.h"
#include "customer.h"
#include "service.h"

Product createProduct()
{
    Product product;

    printf("Enter the product name: ");
    fgets(product.name, PRODUCT_NAME_MAX, stdin);
    dropNewLineFromString(product.name, PRODUCT_NAME_MAX);

    printf("Enter the product price: ");
    scanf("%lf", &product.price);

    return product;
}

void enqueueProduct(CustomerNode* customer, Product productData)
{
    ProductQueue* productQ = customer->data.products;

    if (customer->data.totalItems == productQ->length) {
        printf("[!] Maximum products reached, please checkout.\n");
        return;
    }

    ProductNode* product = malloc(sizeof(ProductNode));

    if (product == NULL) {
        printf("[!] Couldn't allocate a product node.\n");
        return;
    }
    customer->data.totalBill += productData.price;

    product->data = productData;
    product->next = NULL;

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
    ProductNode* product = productQ->start;

    while (product != NULL) {
        ProductNode* tempProduct = product;
        product = product->next;

        free(tempProduct);
    }
    free(productQ);
}

