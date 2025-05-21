#include <stdio.h>
#include <stdlib.h>

#include "customer.h"
#include "product.h"

void finishService(CustomerQueue* customersQ)
{
    while (customersQ->start != NULL) {
        dequeueCustomer(customersQ);
    }
}

void listCustomers(CustomerQueue* customerQ)
{
    printf("[LISTING CUSTOMERS]\n");

    CustomerNode* customer = customerQ->start;

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

void listProducts(ProductQueue* productQ)
{
    printf("[LISTING PRODUCTS]\n");

    ProductNode* product = productQ->start;

    if (product == NULL) {
        printf("[!] There is no products in the customer cart.");
        return;
    }

    int i = 0;

    while (product != NULL) {
        printf("%d - \n", i);
        printf("Name: %s\n", product->data.name);
        printf("Price: %lf\n", product->data.price);
        printf("----------\n");
        product = product->next;
        ++i;
    }
}

unsigned short checkout(CustomerNode* customer)
{
    if (customer == NULL) {
        printf("[!] There is no customer to checkout\n");
        return 0;
    }

    if (customer->data.products->start == NULL) {
        printf("[!] There are no products to be checked out\n");
        return 0;
    }

    double totalPrice = calculateTotalPrice(customer->data.products);

    printf("\n[CHECKOUT]\n");
    printf("Customer name: %s\n", customer->data.name);
    printf("Total bill: %lf\n", totalPrice);

    return 1;
}

unsigned short serviceMenu()
{
    unsigned short choice = 0;

    printf("\n0 - Exit\n");
    printf("1 - Add customer to the end of the line\n");
    printf("2 - Show the customers in the line\n");
    printf("3 - Add a product to the customer cart\n");
    printf("4 - Show the products of the current customer\n");
    printf("5 - Checkout the current customer cart\n");

    printf("Select: ");
    scanf("%hu", &choice);
    getchar();
    printf("\n");

    return choice;
}

void startService(CustomerQueue* customerQ)
{
    unsigned short choice = 0;

    while(1)
    {
        choice = serviceMenu();

        switch(choice) {
            case 0:
                finishService(customerQ);
                return;
            case 1:
                enqueueCustomer(customerQ, createCustomer());
                break;
            case 2:
                listCustomers(customerQ);
                break;
            case 3:
                pushProductIntoCart(customerQ->start, createProduct());
                break;
            case 4:
                listProducts(customerQ->start->data.products);
                break;
            case 5:
                unsigned short wasSuccessful = checkout(customerQ->start);

                if (wasSuccessful == 1) {
                    dequeueCustomer(customerQ);
                }
                break;
        }
    }
}

