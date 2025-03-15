#include <cstddef>
#include <ctime>
#include <iostream>
#include <string>
#include <unordered_map>
#include "Product.h"

Product::Product(const std::string& name, const unsigned int& quantity)
    : id { ++this->lastId }
    , name { name }
    , quantity { quantity }
    , created_at { time(NULL) }
    , updated_at { time(NULL) }
{
}

const void Product::list(const bool& full)
{
    if (Product::products.empty()) {
        std::cout << "\n[NO PRODUCTS AVAILABLE]\n";
        return;
    }

    std::cout << "\n[AVAILABLE PRODUCTS]\n";
    for (auto& product : Product::products) {
        Product* p{ product.second };

        if (full)
            std::cout << "\n[" << p->getId() << "]\n"
                << " | Name: "
                << p->getName() << '\n'
                << " | Quantity: " << p->getQuantity() << '\n'
                << " | Created: " << ctime(&p->created_at)
                << " | Last Updated: " << ctime(&p->updated_at)
                << " -\n";
        else
            std::cout << "\n[" << p->getId() << "] - "
                << p->getName() << '\n';
    }
}

const unsigned int Product::askForId()
{
    if (Product::products.empty()) {
        std::cout << "\n[NO PRODUCTS AVAILABLE]\n";
        return 0;
    }
    Product::list(false);

    unsigned int productId{};
    std::cout << "\nEnter the product id: ";
    std::cin >> productId;

    return productId;
}

const void Product::createOne()
{
    std::cout << "\n[NEW PRODUCT]\n";

    std::string name{};
    unsigned int quantity{};

    std::cout << "Name: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    std::cout << "Quantity: ";
    std::cin >> quantity;

    Product::products[Product::lastId] = new Product(name, quantity);
}

const void Product::restock()
{
    std::cout << "\n[RESTOCK PRODUCT]\n";
    const unsigned int productId{ Product::askForId() };

    if (productId == 0) return;

    if (Product::products.find(productId)
        == Product::products.end()) {
        std::cout << "\n[INVALID PRODUCT ID]\n";
        return;
    }
    Product* p{ Product::products[productId] };

    unsigned int quantityToRestock{};
    std::cout << "How many you want to restock? ";
    std::cin >> quantityToRestock;

    p->setQuantity(p->getQuantity() + quantityToRestock);
    p->updated_at = time(NULL);

    std::cout << "\nQuantity updated: " << p->getQuantity() << '\n';
}

const void Product::use()
{
    std::cout << "\n[USE PRODUCT]\n";
    const unsigned int productId{ Product::askForId() };

    if (productId == 0) return;

    if (Product::products.find(productId)
        == Product::products.end()) {
        std::cout << "\n[INVALID PRODUCT ID]\n";
        return;
    }
    Product* p{ Product::products[productId] };

    unsigned int quantityToUse{};
    std::cout << "\nAvailable quantity: " << p->getQuantity() << '\n';
    std::cout << "How many you want to use? ";
    std::cin >> quantityToUse;

    if (quantityToUse > p->getQuantity()) {
        std::cout << "\n[THE ENTERED QUANTITY EXCEEDS THE AVAILABLE]\n";
        return;
    }
    p->setQuantity(p->getQuantity() - quantityToUse);
    p->updated_at = time(NULL);

    std::cout << "\nQuantity remaining: " << p->getQuantity() << '\n';
}

const void Product::updateOne()
{
    std::cout << "\n[UPDATE PRODUCT]\n";
    const unsigned int productId{ Product::askForId() };

    if (productId == 0) return;

    if (Product::products.find(productId)
        == Product::products.end()) {
        std::cout << "\n[INVALID PRODUCT ID]\n";
        return;
    }
    Product* p{ Product::products[productId] };

    unsigned char answer{};

    std::cout << "\nUpdate name (1 - yes / 0 - no)? ";
    std::cin >> answer;

    if (answer == '1') {
        std::string name{};
        std::cout << "\nEnter the new name: ";
        std::cin.ignore();
        std::getline(std::cin, name);
        p->setName(name);
    }

    std::cout << "\nUpdate quantity (1 - yes / 0 - no)? ";
    std::cin >> answer;

    if (answer == '1') {
        unsigned int quantity{};
        std::cout << "\nEnter the new quantity: ";
        std::cin >> quantity;
        p->setQuantity(quantity);
    }
    p->updated_at = time(NULL);
}

const void Product::deleteOne()
{
    std::cout << "\n[DELETE PRODUCT]\n";
    const unsigned int productId{ Product::askForId() };

    if (productId == 0) return;

    if (Product::products.find(productId)
        == Product::products.end()) {
        std::cout << "\n[INVALID PRODUCT ID]\n";
        return;
    }
    delete Product::products[productId];
    Product::products.erase(productId);

    std::cout << "\n[PRODUCT " << productId
        << " SUCCESSFULLY DELETED]\n";
}

const void Product::deleteAll()
{
    for (auto& product : Product::products) {
        delete product.second;
    }
    Product::products.clear();
}

unsigned int Product::lastId{ 0 };
std::unordered_map<unsigned int, Product*> Product::products{};

