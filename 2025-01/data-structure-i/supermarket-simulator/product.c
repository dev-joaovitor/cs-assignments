#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "product.h"

Product createProduct()
{
    Product product;

    printf("Enter the product name: ");
    fgets(product.name, PRODUCT_NAME_MAX, stdin);

    printf("Enter the product price: ");
    scanf("%lf", &product.price);

    return product;
}

void pushProductIntoCart(CustomerNode* customer, Product product)
{

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

