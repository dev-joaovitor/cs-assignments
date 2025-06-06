#include <stdio.h>
#include <stdlib.h>

#include "customer.h"
#include "product.h"

void dropNewLineFromString(char* string, int length)
{
    int i;
    
    for (i = 0; i < length; ++i) {
        if (string[i] == '\n') {
            string[i] = '\0';
            break;
        }
    }
}

void clearScreen()
{
    int i;
    for (i = 0; i < 200; ++i) {
        printf("\n");
    }
}

void finishService(CustomerQueue* customerQ)
{
    while (customerQ->start != NULL) {
        dequeueCustomer(customerQ);
    }
    free(customerQ);

}

void listCustomers(CustomerQueue* customerQ)
{
    printf("[LISTING CUSTOMERS]\n");

    CustomerNode* customer = customerQ->start;

    if (customer == NULL) {
        printf("[!] There are no customers in the queue.\n");
        return;
    }

    int i = 0;

    while (customer != NULL) {
        printf("+-------------------------------------------------+\n");
        printf("*%d*\n", i);
        printf("Name: %s\n", customer->data.name);
        printf("Total bill: $%.2lf\n", customer->data.totalBill);
        printf("Total products: %d\n", customer->data.totalItems);
        printf("Total products in cart: %d\n", customer->data.products->length);
        customer = customer->next;
        ++i;
    }
    printf("+-------------------------------------------------+\n");
}

void listProducts(ProductQueue* productQ)
{
    printf("[LISTING PRODUCTS]\n");

    ProductNode* product = productQ->start;

    if (product == NULL) {
        printf("[!] There is no products in the customer cart.\n");
        return;
    }

    int i = 0;

    while (product != NULL) {
        printf("+-------------------------------------------------+\n");
        printf("*%d*\n", i);
        printf("Name: %s\n", product->data.name);
        printf("Price: $%.2lf\n", product->data.price);
        product = product->next;
        ++i;
    }
    printf("+-------------------------------------------------+\n");
}

unsigned short checkout(CustomerNode* customer)
{
    if (customer == NULL) {
        printf("\n[!] There is no customer to checkout.\n");
        return 0;
    }

    if (customer->data.products->start == NULL) {
        printf("\n[!] There are no products to be checked out.\n");
        return 0;
    }

    printf("\n[CHECKOUT]\n");
    printf("Customer name: %s\n", customer->data.name);
    printf("Total bill: $%.2lf\n", customer->data.totalBill);

    return 1;
}

unsigned short serviceMenu()
{
    unsigned short choice = 0;

    printf("\n0 - Exit\n");
    printf("1 - Add customer to the end of the queue\n");
    printf("2 - Show the customers in the queue\n");
    printf("3 - Add a product to the current customer cart\n");
    printf("4 - Show the products of the current customer\n");
    printf("5 - Checkout the current customer cart\n");

    printf("Select: ");
    scanf("%hu", &choice);
    getchar();

    clearScreen();

    return choice;
}

void startService(CustomerQueue* customerQ)
{
    unsigned short choice = 0,
        wasSuccessful = 0;

    printf("\n[ ###### Welcome to Yum Yum Market ###### ]\n");

    while(1)
    {
        choice = serviceMenu();

        switch(choice) {
            case 0:
                finishService(customerQ);
                printf("\nCome back soon!\n");
                return;

            case 1:
                enqueueCustomer(customerQ, createCustomer());
                break;

            case 2:
                listCustomers(customerQ);
                break;

            case 3:
                enqueueProduct(customerQ->start, createProduct());
                break;

            case 4:
                if (customerQ->start == NULL) {
                    printf("\n[!] There are no customers in the queue.\n");
                    break;
                }

                listProducts(customerQ->start->data.products);
                break;

            case 5:
                wasSuccessful = checkout(customerQ->start);

                if (wasSuccessful == 1)
                    dequeueCustomer(customerQ);

                wasSuccessful = 0;
                break;
        }
    }
}

