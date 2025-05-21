#include <stdio.h>
#include <stdlib.h>

#include "customer.h"
#include "product.h"

void finishService(CustomerQueue* customersQ)
{
    CustomerNode* customer = customersQ->start;

    while (customer != NULL) {
        CustomerNode* tempCustomer = customer;
        customer = customer->next;

        freeProducts(tempCustomer->data.products);
        free(tempCustomer);
    }
}

void listCustomers(CustomerQueue* customersQ)
{
    printf("[LISTING CUSTOMERS]\n");

    CustomerNode* customer = customersQ->start;

    if (customer == NULL) {
        printf("[!] There is no customer in the queue.");
        return;
    }

    int i = 0;

    while (customer != NULL) {
        printf("%d - \n", i);
        printf("Name: %s\n", customer->data.name);
        printf("Total bill: %lf\n", customer->data.totalBill);
        printf("Total products: %d\n", customer->data.totalItems);
        printf("Total products in cart: %d\n", customer->data.products->length);
        printf("----------\n");
        customer = customer->next;
        ++i;
    }
}

void listProducts(ProductQueue* productsQ)
{
}

void checkout(CustomerNode* customerN)
{
}

unsigned short serviceMenu()
{
    unsigned short choice = 0;

    printf("0 - Exit\n");
    printf("1 - Add customer to the end of the line\n");
    printf("2 - Show the customers in the line\n");
    printf("3 - Add a product to the customer cart\n");
    printf("4 - Show the products of the current customer\n");
    printf("5 - Checkout the current customer cart\n");

    printf("Select: ");
    scanf("%hu", &choice);
    return choice;
}

void startService(CustomerQueue* customersQ)
{
    unsigned short choice = 0,
        error = 0;

    while(1)
    {
        choice = serviceMenu();

        switch(choice) {
            case 0:
                finishService(customersQ);
                return;
            case 1:
                pushCustomerIntoQueue(customersQ, createCustomer());
            case 5:
                checkout(customersQ->start);
                break;
        }

    }
}

