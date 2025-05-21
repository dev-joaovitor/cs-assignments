#include <stdio.h>
#include <stdlib.h>

#include "product.h"
#include "customer.h"
#include "constants.h"

Customer createCustomer()
{
    Customer customer;

    printf("Enter the customer name: ");
    fgets(customer.name, CUSTOMER_NAME_MAX, stdin);

    printf("Enter the number of products: ");
    scanf("%d", &customer.totalItems);
    getchar();

    customer.totalBill = 0;
    customer.products = malloc(sizeof(ProductQueue));

    if (customer.products == NULL)
        return customer;

    customer.products->start = NULL;
    customer.products->end = NULL;

    return customer;
}

void enqueueCustomer(CustomerQueue* customerQ, Customer customer)
{
    if (customer.products == NULL) {
        printf("[!] Customer does not have a valid product list.\n");
        return;
    }

    CustomerNode* customerN = malloc(sizeof(CustomerNode));
    customerN->data = customer;
    customerN->next = NULL;

    customerQ->length++;

    if (customerQ->start == NULL) {
        customerQ->start = customerN;
        customerQ->end = customerN;
        return;
    }
    customerQ->end->next = customerN;
    customerQ->end = customerN;
}

void dequeueCustomer(CustomerQueue* customerQ)
{
    CustomerNode* nextCustomer = customerQ->start->next;

    freeProducts(customerQ->start->data.products);
    free(customerQ->start);

    customerQ->start = nextCustomer;
}

