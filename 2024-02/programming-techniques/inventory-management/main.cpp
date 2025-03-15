#include <iostream>
#include "product/Product.h"
#include "employee/Employee.h"

const void handleEmployeeOptions(unsigned short& option)
{
    std::cout << "\n[LOGIN]\n";
    std::cout << "\n1 - Login";
    std::cout << "\n2 - Register";
    std::cout << "\n0 - EXIT";
    std::cout << "\nSelect an option: ";
    std::cin >> option;
}

const void handleProductOptions(unsigned short& option)
{
    std::cout << "\n[OPTIONS]\n";
    std::cout << "\n1 - Insert product";
    std::cout << "\n2 - Update product";
    std::cout << "\n3 - Use product";
    std::cout << "\n4 - Restock product";
    std::cout << "\n5 - Remove product";
    std::cout << "\n6 - List products";
    std::cout << "\n0 - EXIT";
    std::cout << "\nSelect an option: ";
    std::cin >> option;
}

int main()
{
    unsigned short option{};
    bool isLoggedIn{};

    do {
        if (isLoggedIn) break;

        handleEmployeeOptions(option);
        
        switch(option)
        {
            case 1:
                isLoggedIn = Employee::logIn();

                if (!isLoggedIn)
                    std::cout << "\n[WRONG PASSWORD]\n";
                break;
            case 2:
                if (Employee::registerEmployee())
                    std::cout << "\n[EMPLOYEE SUCCESSFULLY REGISTERED]\n";
                else std::cout << "\n[EMPLOYEE NOT REGISTERED]\n";
                break;
            case 0: break;
            default:
                std::cout << "\n[INVALID OPTION]\n";
        }
    } while(option != 0);

    if (!isLoggedIn) {
        std::cout << "\n[UNAUTHORIZED]\n";
        return 0;
    }

    std::cout << "\n[LOGIN SUCCESSFULL]\n";

    do {
        handleProductOptions(option);

        switch(option)
        {
            case 1:
                Product::createOne();
                break;
            case 2:
                Product::updateOne();
                break;
            case 3:
                Product::use();
                break;
            case 4:
                Product::restock();
                break;
            case 5:
                Product::deleteOne();
                break;
            case 6:
                Product::list(true);
                break;
            case 0: break;
            default:
                std::cout << "\n[INVALID OPTION]\n";
        }
    } while(option != 0);

    Product::deleteAll();

    std::cout << "\nUntil next time =D\n";

    return 0;
}
