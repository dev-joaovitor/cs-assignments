#include <stdio.h>
#include <stdlib.h>

#include "product.h"

Product createProduct()
{
    Product product;

    printf("Enter the product name: ");
    fgets(product.name, 50, stdin);

    printf("Enter the product price: ");
    scanf("%lf", &product.price);

    return product;
}

void pushProductIntoCart(CustomerNode* customer, Product product)
{
    //
}

void freeProducts(ProductQueue* productQ)
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
